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
  Jerarquía de procesos tipo 2
  */
  printf( "SOY EL PROCESO PADRE CON PID: %d\n" , getpid() );
  for (i=1; i < nprocs; i++) {
    if ((childpid= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }
    if (!childpid){
      break;
    }
    wait(&estado);
  }
  if(!childpid)
    printf( "Tengo el PID: %d y mi padre tiene el PID: %d\n" , getpid() , getppid() );

  return 0;
}
