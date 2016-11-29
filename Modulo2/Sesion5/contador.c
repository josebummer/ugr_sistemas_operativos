#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

//Vector donde almacenar el contador de señales

static int contadores[64];

static void mostrarMensaje (int signum) {

 	if (signum >= 1 && signum <= 64) {

 		//Incrementamos el elemento del vector de señales recibidas
 		contadores[signum-1]++;

 		printf("La señal %d se ha recibido %d veces\n", signum, contadores[signum-1]);

 	}
  else {

 		printf("No puedo manejar la señal %d\n", signum);

	}
}

int main(int argc, char *argv[]) {

  //Inicializamos el vector compartido
  for( int i = 0; i < 64; i++ )
    contadores[i] = 0;

	//Declaración de variables
	struct sigaction sig_action;

  if(setvbuf(stdout,NULL,_IONBF,0))
     {
  perror("\nError en setvbuf");
     }

	//Asociamos la funcion definida como manejador
	sig_action.sa_handler = mostrarMensaje;

	//inicializar un conjunto con todas las señales
	//sigfillset(&sig_action.sa_mask);
  sigemptyset (&sig_action.sa_mask);


	sig_action.sa_flags = 0;

	for (int i = 1; i < 63; i++) {
		if ((sigaction(i, &sig_action, NULL)) < 0) {
			printf("La señal %d no se puede manejar.\n" , i);
		}
	}

	//Dejamos en ejecución un bucle infinito, asi el programa no termina
	for(;;){}

}
