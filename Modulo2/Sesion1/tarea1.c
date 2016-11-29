#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>


char buf1[]="abcdefghij";
char buf2[]="ABCDEFGHIJ";

int main(int argc, char *argv[]) {
int fd;

if( (fd=open("archivo",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0) {  //Abrimos el fichero llamado archivo con las opciones necesarias
  printf("\nError %d en open",errno);                           //Si da un numero menor de 0 significa que no se ha abierto correctamentes
  perror("\nError en open");
  exit(-1);                                                     //sale del programa si no se abre el fichero.
}
if(write(fd,buf1,10) != 10) {                 //Escribimos en el fichero, la cadena creada correctamente
  perror("\nError en primer write");          //Si da un numero menor de 0 es que se ha producido un error
  exit(-1);                                   //Si da un numero mayor que 0, da el numero de bytes que se han escrito
}
if(lseek(fd,40,SEEK_SET) < 0) {               //lseek permite colocar el puntero en donde indiquemos
  perror("\nError en lseek");
  exit(-1);                                   //En caso de error se cerrara el programa
}
if(write(fd,buf2,10) != 10) {                 //Escribimos la segunda cadena
  perror("\nError en segundo write");
  exit(-1);
}
close(fd);            //Cerramos el fichero.
return 0;
}
