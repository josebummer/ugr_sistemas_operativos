#include<sys/types.h>
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include<errno.h>

int main( int argc , char * argv[] ){
  if( argc != 2 ){
    printf( "Sintaxis del programa: %s <numero entero>\n" , argv[0] );
    exit(-1);
  }
  int n = atoi(argv[1]);
  pid_t p;
  if( ( p = fork() ) < 0 ){
    perror( "Error en el fork\n" );
    exit(-1);
  }
  if( p == 0 ){
    if( n%2 == 0 ){
      printf( "El numero %d es un numero par (Proceso hijo)\n" , n );
    }
    else{
      printf( "El numero %d es un numero impar (Proceso hijo)\n" , n );
    }
  }
  else{
    if( n%4 == 0 ){
      printf( "El numero %d es divisible entre 4 (Proceso padre)\n" , n );
    }
    else{
      printf( "El numero %d no divisible entre 4 (Proceso padre)\n" , n );
    }
  }
  return 0;
}
