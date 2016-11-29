#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main( int argc , char* argv[] ){
  if( argc < 3 ){
    printf( "Sintaxis del programa: %s '<' || '>' [fichero]\n", argv[0] );
    exit(-1);
  }
  int fd;
  if( (fd = open(argv[3] , O_WRONLY )) < 0 ){
    perror( "Error en open" );
    exit(-1);
  }
  if( *argv[2] == '>' ){
    close(1);
    if( fcntl( fd , F_DUPFD , STDOUT_FILENO ) == -1 ){
      perror( "Error en fcntl" );
      exit(-1);
    }
    execlp( argv[1] , argv[1] , NULL);
  }
  else if( *argv[2] == '<' ){
    close(0);
    if( fcntl( fd , F_DUPFD , STDIN_FILENO ) == -1 ){
      perror( "Error en fcntl" );
      exit(-1);
    }
    execlp( argv[1] , argv[1] , argv[3] , NULL);
  }
}
