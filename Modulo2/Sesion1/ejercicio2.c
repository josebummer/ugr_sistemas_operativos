#include<stdlib.h>                //Desaparecen los Warning
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>

int main(int argc, char *argv[]){
  int fr, fs;
  int i=1,bytes;
  char a[80];
  char texto[9];

  if(argc==2){
    if( (fr=open(argv[1],O_RDONLY,S_IRUSR))<0 ){
      printf("\nError %d en open fichero.",errno);
      perror("\nError en open");
      exit(-1);
    }
  }
  else{
    fr=STDIN_FILENO;
  }


  if( (fs=open("salida.txt",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0 ){
    printf("\nError %d en open.",errno);
    perror("\nError en open");
    exit(-1);
  }

  write(fs,&a,25);
  write(fs,"\n",1);
  while((bytes = read(fr,&a,80))>0){
    sprintf(texto, "Bloque %i\n", i);
		write(fs, &texto, sizeof(texto));
		write(fs, &a, bytes);
		write(fs, "\n", 1);
    i++;
  }
  char totalbloques[26];
  sprintf(totalbloques, "El numero de bloques es %i\n", i-1);
  if(lseek(fs,0,SEEK_SET) < 0) {
		perror("\nError en lseek");
		exit(-1);
	}
  write(fs,totalbloques,26);

  close(fr);
  close(fs);
  return(0);
}
