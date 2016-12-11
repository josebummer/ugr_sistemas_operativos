/*
Reescribir el programa que implemente un encauzamiento de dos órdenes pero
utilizando fcntl. Este programa admitirá tres argumentos. El primer argumento y el tercero
serán dos órdenes de Linux. El segundo argumento será el carácter “|”. El programa deberá
ahora hacer la redirección de la salida de la orden indicada por el primer argumento hacia el
cauce, y redireccionar la entrada estándar de la segunda orden desde el cauce. Por ejemplo,
para simular el encauzamiento ls|sort, ejecutaríamos nuestro programa como:
$> ./ejercicio2 ls “|” sort
*/
// Creado por Jose Antonio Ruiz MIllan

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc , char *argv[]){
  if( argc < 2 ){
    printf("Sintaxis: %s [programa] '|' [programa]",argv[0]);
    exit(-1);
  }
  int fd[2];

  pid_t pid;
  pipe(fd);

  if( (pid = fork()) < 0 ){
    perror("Error en fork");
    exit(-1);
  }
  if( pid == 0 ){
    close(fd[0]);
    close(1);
    if( (fcntl( fd[1], F_DUPFD, STDOUT_FILENO)) < 0 ){
      perror("Error en primer fcntl");
      exit(-1);
    }
    execlp(argv[1],argv[1],NULL);
  }
  else{
    close(fd[1]);
    close(0);
    if( (fcntl( fd[0], F_DUPFD, STDIN_FILENO)) < 0 ){
      perror("Error en segundo fnctl");
      exit(-1);
    }
    execlp(argv[3],argv[3],NULL);
  }
  return 0;
}
