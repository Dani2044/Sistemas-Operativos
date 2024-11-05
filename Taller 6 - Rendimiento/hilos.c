/************************************************************************************************
****************************            Función mult_thread           **************************
************************************************************************************************
Fecha: 31/10/2024
Autor: Daniel Castro
Descripción:
    Este archivo contiene la función de multiplicación de matrices que distribuye las 
    operaciones de cálculo en múltiples hilos.
************************************************************************************************/

#include <pthread.h> // Para manejo de hilos y sincronización
#include "funciones.h" // Librería propia

extern double *mA, *mB, *mC; // Punteros a matrices
extern pthread_mutex_t MM_mutex; // Mutex para sincronización de hilos

void *mult_thread(void *variables){ // Multiplicación de matrices en hilos
	struct parametros *data = (struct parametros *)variables; // Asigna parámetros a la estructura
	
	int idH = data->idH; // ID del hilo
	int nH  = data->nH; // Número de hilos
	int N   = data->N; // Tamaño de la matriz
	int ini = (N/nH)*idH; // Índice de inicio del hilo
	int fin = (N/nH)*(idH+1); // Índice de fin del hilo

    for (int i = ini; i < fin; i++){ // Bucle de filas asignadas al hilo
        for (int j = 0; j < N; j++){ // Bucle sobre columnas
			double *pA, *pB, sumaTemp = 0.0; // Punteros y suma temporal
			pA = mA + (i*N); // Apunta a la fila de mA
			pB = mB + j; // Apunta a la columna de mB
            for (int k = 0; k < N; k++, pA++, pB+=N){ // Bucle de cálculo
				sumaTemp += (*pA * *pB); // Suma producto
			}
			mC[i*N+j] = sumaTemp; // Almacena resultado en mC
		}
	}

	pthread_mutex_lock (&MM_mutex); // Bloquea mutex para sincronización
	pthread_mutex_unlock (&MM_mutex); // Desbloquea mutex
	pthread_exit(NULL); // Termina el hilo
}