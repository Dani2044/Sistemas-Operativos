/************************************************************************************************
Fecha: 7/11/2024
Autor: Daniel Castro
Materia: Sistemas Operativos
Tema: Evaluación parcial
Descripción:
	Este fichero implementa la función secundaria que realiza la cuenta e impresión del 0 y
    último valor del ciclo.
************************************************************************************************
            FUNCIÓN SECUNDARIA
************************************************************************************************/

#include "hilos.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

// Definición del mutex
extern pthread_mutex_t BLOQUEO;

/* Función que ejecutarán los hilos */
void *funcion(void *job) {
    pthread_mutex_lock(&BLOQUEO); // Bloquea el mutex hasta que se termine de ejecutar

    size_t IDh = *(size_t *)job; // Convierte el valor recibido a size_t y lo desreferencia
    int cont = 5; // Crea un contador
    printf("\nHilo %zu ha iniciado\n", IDh); // Imprime su inicio

    for (int i = 0; i < 299; i++) { // Realiza la cuenta de 300 enteros 
        if (i == 0 || i == 299) { // Imprime el 0 o último valor del bucle
            printf("\nValor: %d", i);
        }
        cont += i; // Aumenta el contador
    }

    printf("\nHilo %zu ha finalizado\n", IDh); // Imprime su fin
    pthread_mutex_unlock(&BLOQUEO); // Desbloquea el mutex

    return NULL;
}