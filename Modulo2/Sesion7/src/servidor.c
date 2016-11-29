#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

#define tamano 1024
#define longnombre 50
#define nombloqueo "archproxy"

// Manejador de senal (SIGCHL) para procesos zombies
static void mimanejador(int senal){
  while(wait(NULL) > 0);
}

int main( int argc , char **argv) {

  dup2(STDOUT_FILENO, STDERR_FILENO);

  setbuf(stdout, NULL);

  if ( argc != 2 ){
    printf("Sintaxis: %s <nombrefifo>\n", argv[0]);
    exit(-1);
  }
  int dfifoe , dfifos, tamanio , pid;
  char nombrefifoe[longnombre], nombrefifos[longnombre], buffer[tamano];

  sprintf( nombrefifoe, "%se", argv[1] );
  sprintf( nombrefifos, "%ss", argv[1] );

  unlink(nombrefifoe);
	unlink(nombrefifos);

  umask(0);
  if( (mkfifo(nombrefifoe,0777)) == -1){
    perror ("Servidor: Problema al crear el archivo fifo de entrada.");
    exit(1);
  }

  if( (mkfifo(nombrefifos,0777)) == -1){
    perror ("Servidor: Problema al crear el archivo fifo de salida.");
    exit(1);
  }

  if( (dfifoe = open(nombrefifoe,O_RDWR)) == -1){
    perror ("Servidor: Problema con el archivo fifo de entrada.");
    exit(1);
  }
  if( (dfifos = open(nombrefifos,O_RDWR)) == -1){
    perror ("Servidor: Problema con el archivo fifo de salida.");
    exit(1);
  }

  char nombre[tamano];
  int fd, p;
  while(1) {
    memset(buffer,0,tamano);
    if (tamanio = read (dfifoe,buffer,sizeof(int))) {
      if ( (pid = fork()) == -1 ){
        perror("Error al crear el hijo");
        exit(-1);
      }
      if( pid == 0 ){
        p = getpid();

      	//Genero el nombre
      	sprintf(nombre, "fifo.%d",p);

      	//Creo un FIFO
        if( (mkfifo(nombre,0777)) == -1){
          perror ("Servidor: Problema al crear el archivo proxy.");
          exit(1);
        }
        if(write(dfifos,&p,sizeof(int))<0){
          perror("Error en write\n");
          exit(EXIT_FAILURE);
        }

      	//Abro el FIFO
      	fd=open(nombre,O_RDWR);
      	if(fd<0){
      		perror("Error en write\n");
      		exit(EXIT_FAILURE);
      	}

      	//Redirigo la entrada estándar al archivo
      	dup2(fd, STDIN_FILENO);

      	//Ejecuto el proxy
      	execlp("./proxy", "./proxy", NULL);

      	//Si no pasa al codigo del proxy es que ha dado error, asi que lo pintamos
      	perror("Fallo en execlp");
      	exit(EXIT_FAILURE);
      }
      signal(SIGCHLD , mimanejador);
    }
  }
  return 0;
}
