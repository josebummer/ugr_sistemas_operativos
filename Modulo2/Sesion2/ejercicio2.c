#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include <dirent.h>
#include<errno.h>

int main(int argc, char *argv[]){
  if(argc!=3){
    printf("Sintaxis del programa: %s [directorio] [permisos octal]\n",argv[0]);
    exit(-1);
  }
  DIR *directorio;
  int permisos_n,permisos_v;
  struct dirent *archivos;
  struct stat atributos;

  if((directorio=opendir(argv[1]))==NULL){
    printf("Error: no se puede abrir el directorio %s.\n",argv[1]);
    exit(-1);
  }
  while((archivos=readdir(directorio))!=NULL){
    chdir(argv[1]);
    if((stat(archivos->d_name,&atributos))<0){
      printf("Error al leer los atributos del fichero %s.\n",archivos->d_name);
    }
    else{
      if(!S_ISDIR(atributos.st_mode)){
        permisos_n=strtol(argv[2],0,8) & 0777;
        permisos_v=atributos.st_mode & 0777;
        if((errno=chmod(archivos->d_name,permisos_n))<0){
          printf("%s : \t%d \t%o\n",archivos->d_name,errno,permisos_v);
        }
        else{
          printf("%s : \t%o \t%o\n",archivos->d_name,permisos_v,permisos_n);
        }

      }
    }
  }
  closedir(directorio);

  return 0;
}
