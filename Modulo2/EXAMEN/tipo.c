// APELLIDOS: RUIZ MILLAN

// NOMBRE: JOSE ANTONIO

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <ftw.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

int main( int argc , char *argv[]){//0
	if( argc != 2 ){//1
		printf("Sintaxis: %s directorio\n",argv[0]);
		printf("RECUERDA: directorio sin '/' al final\n");
		exit(-1);
	} //1
	DIR *dir;
	struct dirent *archivos;
	int fd;
	char nomarch[NAME_MAX];
	char ruta[PATH_MAX];
	char rutanueva[PATH_MAX];
	struct stat atributos;
	pid_t pid;
	int estado;

	if( (dir = opendir(argv[1])) == NULL ){//2
		printf("Error en opendir.");
		exit(-1);
	}//2
	while( (archivos = readdir(dir)) != NULL ){//3
		sprintf(ruta,"%s/%s",argv[1],archivos->d_name);		//El directorio tanto absoluto como relativo se tiene que escribir sin '/' al final
		if((stat(ruta,&atributos))<0){//4
      			printf("Error al leer los atributos del fichero %s.\n",archivos->d_name);
			exit(-1);
    		}//4
		if(!S_ISDIR(atributos.st_mode)){//5
			sprintf(rutanueva,"%s-tipo/%s-tipo",argv[1],archivos->d_name); //asumimos que el directorio esta creado.
			umask(0);
			if( (fd = open(rutanueva,O_RDWR|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0 ){//6
				perror("Error en open");
				exit(-1);
			}//6
			char p[NAME_MAX];
			int tamanio = sprintf(p,"Usuario: %d",atributos.st_uid);
			if( (write(fd,p,tamanio)) < 0){
				perror("Error en write");
				exit(-1);
			}
			write(fd,"\n",1);
			if( atributos.st_mode & S_ISUID ){
				tamanio = sprintf(p,"SUID: true");
				if( (write(fd,p,tamanio)) != tamanio){
					perror("Error en write");
					exit(-1);
				}
			}
			else{
				tamanio = sprintf(p,"SUID: false");
				if( (write(fd,p,tamanio)) != tamanio){
					perror("Error en write");
					exit(-1);
				}
			}
			write(fd,"\n",1);
			if( (pid = fork()) < 0 ){//7
				perror("Error en fork");
				exit(-1);
			}//7
			if( pid == 0 ){//8
				dup2(fd,STDOUT_FILENO);
				if( (execlp("file","file",ruta,NULL)) == -1 ){
					perror("Error en execlp.");
					exit(-1);
				}
			}//8
			if( waitpid( pid , &estado , 0 ) < 0 ){
				printf("Acaba de finalizar mi hijo con PID:%d danda el error: %d\n", pid, errno );
				perror("Error al finalizar un hijo");
			}
		}//5
	}//3
	close(fd);
	exit(0);
}//0
