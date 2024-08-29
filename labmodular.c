/*****************************************************************************

Fecha:   29/08/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio de Compilación Modular

        - Funcionamiento del código
        - Modularización del código
        - Creación de fichero de Automatización de Compilación
      
******************************************************************************
        Función Principal
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "librerialab.h"

/* Programa principal */
int main() {
  vectorDinamico editor;
  vectorInicio(&editor);

  addVector(&editor, "Hola");
  addVector(&editor, "Profesional");
  addVector(&editor, "en");
  addVector(&editor, "Formación");
  addVector(&editor, "de");
  addVector(&editor, "Ingeniería");

  printf("\n");

  for (int i = 0; i < totalVector(&editor); i++) {
    printf("%s ", (char *)getVector(&editor, i));
  }

  printf("\n");

  /* Se borra los elementos del 2 al 5 */
  int a = 5;
  while (a > 1) {
    borrarVector(&editor, a);
    a--;
  }

  setVector(&editor, 1, "Buenos");
  addVector(&editor, "Días");

  printf("\n");

  for (int i = 0; i < totalVector(&editor); i++) {
    printf("%s ", (char *)getVector(&editor, i));
  }

  printf("\n");
  freeVector(&editor);

  return 0;
}