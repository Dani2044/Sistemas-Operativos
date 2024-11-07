/************************************************************************************************
Fecha: 7/11/2024
Autor: Daniel Castro
Materia: Sistemas Operativos
Tema: Evaluación parcial
Descripción:
	Este fichero crea 5 hilos, los cuales ejecutan una función que realiza la cuenta de 300
    enteros e imprime el 0 y último valor. Además, imprime en orden "Hilo ID iniciado" e
    "Hilo ID finalizado".
************************************************************************************************
            FUNCIÓN PRINCIPAL
************************************************************************************************/
/* Importación de librerías */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "hilos.h"

pthread_mutex_t BLOQUEO; // Definición del mutex

int main() {
    size_t jobs[5]; // Crea 5 jobs
    pthread_t hilos[5]; // Crea 5 hilos
    int i = 0;
    int error;

    if (pthread_mutex_init(&BLOQUEO, NULL) != 0) { // Inicializa el mutex y verifica error
        printf("\nFallo de inicialización de MUTEX\n");
        return 1;
    }

    while (i < 5) { // Itera sobre los 5 hilos
        jobs[i] = i;
        error = pthread_create(&hilos[i], NULL, &funcion, jobs + i); // Crea los hilos y les asigna la función y parámetro que debe ejecutar
        if (error != 0) {
            printf("\nError en la creación de hilos: [%s]\n", strerror(error)); // Convierte el mensaje de error a un string
        }
        i++; // Aumenta el contador
    }

    // Espera a que los hilos terminen
    pthread_join(hilos[0], NULL);
    pthread_join(hilos[1], NULL);
    pthread_join(hilos[2], NULL);

    // Destruye el mutex
    pthread_mutex_destroy(&BLOQUEO);

    return 0;
}