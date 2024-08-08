/******************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 8/08/24
Tema: Asignación de memoria dinámica
      Asignación de memoria en Bytes de almacenamiento
*******************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int var = 480;
  int *varptr = &var;
  int **dobleptr = &varptr;
  printf("Valor de la variable \t\t= %d\n", var);
  printf("Valor del puntero \t\t= %d\n", *varptr);
  printf("Valor del puntero doble \t\t= %d\n", **dobleptr);
  
  printf("Dirección de la variable \t\t= %p\n", &varptr);
  
  printf("Dirección del puntero \t\t= %p\n", &varptr);
  printf("Valor en el puntero \t\t= %p\n", varptr);
  
  printf("Dirección del puntero doble \t\t= %p\n", &dobleptr);
  printf("Valor en el puntero doble \t\t= %p\n", dobleptr);
  
  return 0;
}
