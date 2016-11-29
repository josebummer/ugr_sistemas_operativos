#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int nele(int n){
  int res=1;
  while(n/10>0){
    n=n/10;
    res++;
  }
  return res;
}

int main(int argc , char* argv[]){
  if(argc != 3){
    printf("Sintaxis del programa 'maestro': %s <numero inicial> <numero final>\n" , argv[0]);
    exit(-1);
  }
  pid_t PID;
  int p1[2] , p2[2];
  int ini = atoi(argv[1]);
  int fin = atoi(argv[2]);
  int mitad = (ini + fin) / 2;
  int numBytes;
  char buffer[80];
  char par_med[nele(mitad)+1];

  sprintf(par_med,"%d",mitad);

  pipe(p1);
  pipe(p2);

  if((PID = fork())<0){
    perror("Error en el fork");
    exit(-1);
  }
  if(PID == 0){
    close(p1[0]);

    dup2(p1[1],STDOUT_FILENO);

    execlp("./esclavo" , "esclavo" , argv[1] ,par_med, NULL);
  }
  if((PID = fork())<0){
    perror("Error en el fork");
    exit(-1);
  }
  if(PID == 0){
    close(p2[0]);

    dup2(p2[1],STDOUT_FILENO);
    sprintf(par_med,"%d",mitad+1);
    execlp("./esclavo" , "esclavo" , par_med , argv[2] , NULL);
  }

  close(p1[1]);

  dup2(p1[0],STDIN_FILENO);
  printf("Numeros primos:\n");
  while((numBytes=read(p1[0],&buffer,sizeof(buffer)))>0)
    write(STDOUT_FILENO,&buffer,numBytes);

  close(p2[1]);

  dup2(p2[0],STDIN_FILENO);
  while((numBytes=read(p2[0],&buffer,sizeof(buffer)))>0)
    write(STDOUT_FILENO,&buffer,numBytes);

  return 0;
}
