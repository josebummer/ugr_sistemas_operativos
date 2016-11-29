#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include<errno.h>
#include <sys/wait.h>

int main(){
  int i , estado , pidpadre;
  const int nprocs = 5;
  pid_t childpid[nprocs];

 printf( "PID PADRE: %d\n" , pidpadre = getpid() );
  for (i=0; i < nprocs; i++) {
    if ((childpid[i]= fork()) == -1) {
      fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
      exit(-1);
    }
    if (!childpid[i]){
      break;
    }
  }
  if( getpid() != pidpadre)
    printf( "Soy el hijo con PID: %d\n" , getpid() );

  for( i = 0; i < nprocs; i++){
    if( waitpid( childpid[i] , &estado , 0 ) > 0 ){
      printf("Acaba de finalizar mi hijo con PID:%d\n", childpid[i] );
	    printf("Solo me quedan %d hijos vivos\n", nprocs - (i+1) );
    }
  }

  exit(0);
}
