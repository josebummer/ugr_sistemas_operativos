#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include<errno.h>
#include <sys/wait.h>

int main(){

  int nprocs = 21 , i = 0 , estado;
  pid_t childpid;

/*
Jerarquía de procesos tipo 1
*/
  printf( "Vamos a crear 20 hijos recursivos:\n" );
  for (i=0; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }
    if (childpid){
      break;
    }
    printf( "%d.- Tengo el PID: %d y mi padre tiene el PID: %d\n" , i+1 , getpid() , getppid() );
  }
  wait(&estado);
  return 0;
}
