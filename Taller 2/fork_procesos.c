/*****************************************************************************

Fecha:   3/10/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio Fork-Pipe-Name

  - Fork procesos

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void creacion_fork(int linea){
  pid_t proceso; 
  proceso = fork();
  if(proceso<0){ // -1 para error
    printf("Error creación proceso\n");
    exit(1);
  } else if (proceso==0) // -1 hijo
    printf("%d: Proceso =HIJO=: %d\n",linea, getpid());
  else // 1 para padre
    printf("%d: Proceso =PADRE= %d\n",linea, getpid());
}

int main(int argc, char *argv[]){
  int p = (int) atoi(argv[1]);
  for(int i=0; i<p; i++) {
    creacion_fork(i);
  }
  printf("\n---\n\n");
  return 0;
}