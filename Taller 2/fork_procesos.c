/*****************************************************************************

Fecha:   3/10/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio Fork-Pipe-Name

  - Fork procesos: Demuestra el uso de "fork()",
    que genera un proceso hijo idéntico al padre,
    replicando este proceso en varias generaciones.

*****************************************************************************/

#include <stdio.h>  // Para entradas y salidas estándar
#include <stdlib.h> // Para manejo de memoria y utilidades generales
#include <unistd.h> // Para llamadas al sistema como fork()
#include <sys/types.h> // Para definir tipos de datos como pid_t

void creacion_fork(int linea){
  pid_t proceso; // Identificador de proceso
  proceso = fork(); // Crea un nuevo proceso
  if(proceso < 0){ // Error en la creación del proceso (-1)
    printf("Error en la creación del proceso\n");
    exit(1); // Termina el programa con error
  } else if (proceso == 0) // Caso del proceso hijo (0)
    printf("%d: Proceso =HIJO=: %d\n", linea, getpid()); // Muestra el número de línea y el ID del hijo
  else // Caso del proceso padre (1)
    printf("%d: Proceso =PADRE= %d\n", linea, getpid()); // Muestra el número de línea y el ID del padre
}

int main(int argc, char *argv[]){
  int p = (int) atoi(argv[1]); // Convierte el argumento de entrada en entero
  for(int i = 0; i < p; i++) { // Llama a creacion_fork() las veces ingresadas al ejecutar el programa
    creacion_fork(i);
  }
  printf("\n---\n\n");
  return 0; // Finaliza el programa
}