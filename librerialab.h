/*****************************************************************************

Fecha:   29/08/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio de Compilación Modular

        - Funcionamiento del código
        - Modularización del código
        - Creación de fichero de Automatización de Compilación
      
******************************************************************************
      INTERFAZ DE LIBRERÍA DE FUNCIONES: MENÚ DE FUNCIONES
*****************************************************************************/

#ifndef _LIBRERIALAB_H_
#define _LIBRERIALAB_H_

#define CAPACIDAD_INICIAL 4

/* Creación de estructura de datos para el vector */
typedef struct {
  int capacidad;
  int totalElementos;
  void **elementos;
} vectorDinamico;

/* Inicialización de los valores del vector, reserva de memoria */
void vectorInicio(vectorDinamico *V);

/* Retorna el total de elementos */
int totalVector(const vectorDinamico *V);

/* Redimensiona el vector */
static void resizeVector(vectorDinamico *V, int capacidad);

/* Agregar elementos al vector */
void addVector(vectorDinamico *V, void *elemento);

/* Liberación de memoria dinámica */
void freeVector(vectorDinamico *V);

/* Obtener un elemento en el índice dado */
void *getVector(const vectorDinamico *V, int indice);

/* Establecer un elemento en el índice dado */
void setVector(vectorDinamico *V, int indice, void *elemento);

/* Borrar un elemento según el índice, y redimensionar si es necesario */
void borrarVector(vectorDinamico *V, int indice);

#endif