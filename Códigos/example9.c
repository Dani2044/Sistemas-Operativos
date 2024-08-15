/*************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 1/08/24
Tema: Sistemas operativos, parte 2
**************************************************/

#include <stdio.h>
#include <stdlib.h>

#define size 10

int main(int argc, char *argv[]){
  /*** Suma de dos valores ingresados por pantalla usando punteros ***/
  int valor1, valor2; //--> Variables de tipo entero
  int *ptrV1, *ptrV2; //--> Punteros de tipo entero
  ptrV1 = &valor1; //--> Apuntar a la dirección de la variable
  ptrV2 = &valor2; //--> Apuntar a la dirección de la variable
  printf("\nIngrese dos valores a ser sumados:\n");
  scanf("%d %d", &valor1, &valor2);
  printf("\nLa suma es: %d\n", (*ptrV1 + *ptrV2));
  return 0;
}