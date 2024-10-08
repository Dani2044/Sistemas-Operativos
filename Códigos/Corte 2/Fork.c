/*****************************************************************************

Fecha:   26/09/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Fork inicial
      
*****************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  int x;
  for(x=0;x<5;x++) {
    fork();
    printf("The process ID (PID): %d \n",getpid());           
  }
  return 0;
}