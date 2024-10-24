/************************************************************************************************
Fecha: 24/10/2024
Autor: Daniel Castro
Materia: Sistemas Operativos
Tema: Taller 5 - Máquina Virtual

Descripción:
        Programa que simula la sincronización entre un productor y un consumidor utilizando 
        hilos y variables de condición para gestionar un contador de productos.
************************************************************************************************/
#include <stdio.h> // Para estándar de entrada/salida
#include <stdlib.h> // Para uso de funciones como rand()
#include <pthread.h> // Para manejo de hilos y sincronización
#include <unistd.h> // Para usar funciones como sleep()

int counter = 0; // Contador de elementos
int max = 4; // Límite superior del contador

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex para contador
pthread_cond_t condVarProd = PTHREAD_COND_INITIALIZER; // Condición para productor
pthread_cond_t condVarCons = PTHREAD_COND_INITIALIZER; // Condición para consumidor

// Función que ejecuta el hilo productor
void *productor(void *arg) {
    while(1) {                    
        pthread_mutex_lock(&counter_mutex); // Bloquea el acceso al contador

        while (counter >= max) {                      
            pthread_cond_wait(&condVarProd, &counter_mutex); // Espera si contador está lleno
        }

        counter++; // Incrementa el contador
        printf("Soy productor %ld valor contador = %d\n", pthread_self(), counter); // Imprime estado
        
        pthread_cond_signal(&condVarCons); // Despierta al consumidor
        pthread_mutex_unlock(&counter_mutex); // Desbloquea el contador

        sleep(1); // Simula tiempo de producción
    }
    return NULL;
}

// Función que ejecuta el hilo consumidor
void *consumidor(void *arg) {
    while(1) {   
        sleep(1);                 
        pthread_mutex_lock(&counter_mutex); // Bloquea el acceso al contador

        while (counter <= 0) {                      
            pthread_cond_wait(&condVarCons, &counter_mutex); // Espera si contador está vacío
        }

        counter--; // Decrementa el contador
        printf("Soy consumidor %ld valor contador = %d\n", pthread_self(), counter); // Imprime estado

        pthread_cond_signal(&condVarProd); // Despierta al productor
        pthread_mutex_unlock(&counter_mutex); // Desbloquea el contador
    }
    return NULL;
}

// Función principal
int main() {
    pthread_t proHilo[5], conHilo[5]; // Declaración de hilos productor y consumidor
    int i;

    for(i = 0; i < 5; i++) {
        pthread_create(&proHilo[i], NULL, productor, NULL); // Crea hilo para el productor
        pthread_create(&conHilo[i], NULL, consumidor, NULL); // Crea hilo para el consumidor
    }

    for(i = 0; i < 5; i++) {
        pthread_join(proHilo[i], NULL); // Espera a que termine el hilo productor
        pthread_join(conHilo[i], NULL); // Espera a que termine el hilo consumidor
    }

    return 0;
}