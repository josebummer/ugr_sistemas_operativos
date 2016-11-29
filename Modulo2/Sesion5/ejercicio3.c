#include <stdio.h>
#include <signal.h>

int main()

{
sigset_t new_mask;

/* inicializar la nueva mascara de se�ales */
sigemptyset(&new_mask);

for(int i = 1; i <= 64 ; i++)
  if( i != SIGUSR1 )
    sigaddset(&new_mask, i);

/*esperamos todas las señales mesnos SIGUSR1 */
sigsuspend(&new_mask);

}
