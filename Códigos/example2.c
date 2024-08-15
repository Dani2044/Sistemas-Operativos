/*************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 1/08/24
Tema: Sistemas operativos, parte 2
**************************************************/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
  int x;
  int suma = 0;
  
  do{
    // Leer valores por consola
    scanf("%d", &x);
    // Calcular suma
    suma += x;
  } while(x != 0);
  // Imprimir
  printf("La suma es: %d.\n", suma);
  return 0;
}
