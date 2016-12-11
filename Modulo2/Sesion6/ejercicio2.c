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
    dup2(fd[1],STDOUT_FILENO);
    execlp(argv[1],argv[1],NULL);
  }
  else{
    close(fd[1]);
    dup2(fd[0],STDIN_FILENO);
    execlp(argv[3],argv[3],NULL);
  }
}
