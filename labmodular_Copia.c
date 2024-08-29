/*****************************************************************************

Fecha:   29/08/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio de Compilación Modular

        - Funcionamiento del código
        - Modularización del código
        - Creación de fichero de Automatización de Compilación
      
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 4

/* Creación de estructura de datos para el vector */
typedef struct {
  int capacidad;
  int totalElementos;
  void **elementos;
} vectorDinamico;

/* Inicialización de los valores del vector, reserva de memoria */
void vectorInicio(vectorDinamico *V) {
  V->capacidad = CAPACIDAD_INICIAL;
  V->totalElementos = 0;
  V->elementos = malloc(sizeof(void *) * V->capacidad); 
}

/* Retorna el total de elementos */
int totalVector(const vectorDinamico *V) {
  return V->totalElementos;
}

/* Redimensiona el vector */
static void resizeVector(vectorDinamico *V, int capacidad) {
  printf("Redimension: %d a %d \n", V->capacidad, capacidad);

  void **elementos = realloc(V->elementos, sizeof(void *) * capacidad);
  if (elementos) {
    V->elementos = elementos;
    V->capacidad = capacidad;
  }
}

/* Agregar elementos al vector */
void addVector(vectorDinamico *V, void *elemento) {
  if (V->capacidad == V->totalElementos) {
    resizeVector(V, V->capacidad * 2);
  }
  V->elementos[V->totalElementos++] = elemento;
}

/* Liberación de memoria dinámica */
void freeVector(vectorDinamico *V) {
  free(V->elementos);
  V->elementos = NULL;
  V->capacidad = 0;
  V->totalElementos = 0;
}

/* Obtener un elemento en el índice dado */
void *getVector(const vectorDinamico *V, int indice) {
  if (indice >= 0 && indice < V->totalElementos) {
    return V->elementos[indice];
  }
  return NULL;
}

/* Establecer un elemento en el índice dado */
void setVector(vectorDinamico *V, int indice, void *elemento) {
  if (indice >= 0 && indice < V->totalElementos) {
    V->elementos[indice] = elemento;
  }
}

/* Borrar un elemento según el índice, y redimensionar si es necesario */
void borrarVector(vectorDinamico *V, int indice) {
  if (indice < 0 || indice >= V->totalElementos) {
    return; 
  }

  for (int i = indice; i < V->totalElementos - 1; i++) {
    V->elementos[i] = V->elementos[i + 1];
  }
  V->totalElementos--;

  if (V->totalElementos > 0 && V->totalElementos == V->capacidad / 4) {
    resizeVector(V, V->capacidad / 2);
  }
}

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