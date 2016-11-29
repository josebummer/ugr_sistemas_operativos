#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define tamano 1024
#define longnombre 50

void bloqueodesbloqueo(int dbloqueo, int orden) {

	struct flock cerrojo;

	// Inicializamos el cerrojo para bloquear todo el archivo
	cerrojo.l_type= orden;
	cerrojo.l_whence= SEEK_SET;
	cerrojo.l_start= 0;
	cerrojo.l_len = 0;

	//Si vamos a bloquearlo y ya lo esta, entonces el proceso duerme
	if (fcntl(dbloqueo, F_SETLKW, &cerrojo) == -1) {
		perror ("Proxy: problemas al bloquear para impresion");
		exit(1);
	}
}

int main( ){
	dup2(STDOUT_FILENO,STDERR_FILENO);
  int tamanio;
  char buffer[tamano], nom[tamano];

  FILE *tmpFile = tmpfile();

  tamanio = read(STDIN_FILENO, buffer , tamano);
  if(tamanio==-1){
	    perror("Error en la lectura en del proxy.\n");
	      exit(EXIT_FAILURE);
  }
	  while(tamanio > 0){
		if(fwrite(buffer,sizeof(char),sizeof(buffer),tmpFile)==-1){
			perror("Error en fwrite la escritura del proxy1\n");
			exit(EXIT_FAILURE);
		}
		if(tamanio != tamano)
			break;
		memset(buffer,0,tamano);
		tamanio=read(STDIN_FILENO,buffer,sizeof(buffer));
		if(tamanio==-1){
			perror("Error en la lectura en del proxy2\n");
			exit(EXIT_FAILURE);
		}
	}
	memset(buffer,0,tamano);
	rewind(tmpFile);
  bloqueodesbloqueo(STDOUT_FILENO,F_WRLCK);
  tamanio=fread(buffer,sizeof(char),sizeof(buffer),tmpFile);
  if(tamanio==-1){
      perror("Error en fread la lectura en proxy.\n");
      exit(EXIT_FAILURE);
  }
  while( tamanio > 0 ){
    if(write(STDOUT_FILENO,buffer,sizeof(buffer))==-1){
				perror("Error en la escritura del proxy1\n");
				exit(EXIT_FAILURE);
		}
		memset(buffer,0,tamano);
    tamanio=fread(buffer,sizeof(char),sizeof(buffer),tmpFile);
		if(tamanio ==- 1) {
			perror("Error en la fread lectura en del proxy2\n");
			exit(EXIT_FAILURE);
		}
  }
  bloqueodesbloqueo(STDOUT_FILENO,F_UNLCK);

  fclose(tmpFile);
	sprintf(nom,"fifo.%d",getpid());
	unlink(nom);
	exit(EXIT_FAILURE);
}
