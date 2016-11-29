#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <ftw.h>

int main(int argc,char *argv[]){

  if(argc>2){
    printf("Sintaxis del programa: %s <pathname>\n",argv[0]);
    exit(-1);
  }
  DIR *directorio;
  struct dirent *archivos;
  struct stat atributos;
  int size=0,nfilas=0;

  if(argc==1){
    if((directorio=opendir("."))<0){
      printf("Error, no se puede abrir el directorio ./\n");
      exit(-1);
    }
  }
  else{
    if((directorio=opendir(argv[1]))<0){
      printf("Error, no se puede abrir el directorio %s\n",argv[1]);
      exit(-1);
    }
    chdir(argv[1]);
  }
  printf("Los i-nodos son:\n");
  while((archivos=readdir(directorio))!=NULL){
    if((stat(archivos->d_name,&atributos))<0){
      printf("Error al leer los atributos del archivo %s\n",archivos->d_name);
    }
    else{
      if ((S_ISREG(atributos.st_mode)) && (atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){
        printf("%s %llu\n",archivos->d_name, atributos.st_ino);
        size += atributos.st_size;
	      nfilas++;
      }
    }
  }
  printf("Existen %d archivos regulares con permiso x para grupo y otros\n",nfilas);
  printf("El tamaño total ocupado por dichos archivos es %d bytes\n",size);
  closedir(directorio);
}
