#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <stdbool.h>

int main(int argc , char* argv[]){
  if(argc != 3){
    printf("Sintaxis del programa 'esclavo': %s <valor minimo> <valor maximo>\n" , argv[0]);
    exit(-1);
  }
  bool primo;
  int ini = atoi(argv[1]);
  int fin = atoi(argv[2]);

  for(int i = ini ; i < fin ; i++){
    primo = true;
    for(int j = 2 ; j <= sqrt(i) && primo ; j++)
      if(i%j == 0)
        primo = false;
    if(primo)
      printf("El %d es un numero primo\n" , i);
  }

  return 0;
}
