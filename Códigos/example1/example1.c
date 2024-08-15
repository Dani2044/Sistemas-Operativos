/*************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 25/07/24
Tema: Entradas y salidas en C
**************************************************/

#include <stdio.h>
// Incluir header
#include "funciones.h"

int main(int argc, char *argv[]) {  
  //Menú
  int o;
  do {
    printf("----------------------------------------------------------\n");
    printf("Bienvenido al programa.\n");
    printf("0. Salir.\n1. Sumar dos números.\n2. Calcular el área de un círculo.\n3. Calcular el volumen de una circunferencia.\n4. Calcular el volumen de un cono.\n5. Calcular la tangente.\n");
    printf("Ingrese el número correspondiente a una de las anteriores opciones:\n");
    scanf("%d", &o);
    switch (o) {
      case 0:
        printf("Gracias por utilizar este programa.\n");
        break;
      case 1:
        fsuma();
        break;
      case 2:
        farea();
        break;
      case 3:
        fcir();
        break;
      case 4:
        fcono();
        break;
      case 5:
        ftg();
        break;
      default:
        printf("Opción no válida.\n");
        break;
    }
  } while (o != 0);
  
  return 0;
}
