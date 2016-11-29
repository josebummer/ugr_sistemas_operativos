#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <ftw.h>

int n_files = 0;
int size = 0;

int visitar(const char* path, const struct stat* stat, int flags, struct FTW* ftw) {

	if ((S_ISREG(stat->st_mode)) && (stat->st_mode & S_IXGRP) && (stat->st_mode & S_IXOTH)) {

	    printf("%s %llu\n",path, stat->st_ino);

	    size += stat->st_size;
	    n_files++;

	}

	return 0;
}

int main(int argc, char *argv[])
{

	printf("Los i-nodos son:\n");

    if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
        perror("nftw");
    }


	printf("Existen %d archivos regulares con permiso x para grupo y otros\n",n_files);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n",size);

	return 0;

}
