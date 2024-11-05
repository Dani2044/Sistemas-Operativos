/************************************************************************************************
****************************         Función Principal         *******************************
************************************************************************************************
Fecha: 31/10/2024
Autor: Daniel Castro
Materia: Sistemas Operativos
Tema: Taller 6 - Evaluación de rendimiento
Descripción:
    Este archivo contiene la función principal que configura la ejecución y crea los hilos para
    realizar la multiplicación de matrices cuadradas N×N empleando el modelo de hilos POSIX 
    (Pthreads). Se encarga de gestionar el tiempo de ejecución del algoritmo de multiplicación.
************************************************************************************************/

#include <stdio.h> // Para entradas y salidas estándar
#include <pthread.h> // Para manejo de hilos y sincronización
#include <stdlib.h> // Para uso de funciones básicas
#include <sys/time.h> // Para medición de tiempos
#include "funciones.h" // Librería propia

#define DATA_SIZE (1024*1024*64*3) // Tamaño del buffer de datos

pthread_mutex_t MM_mutex; // Mutex global para sincronización
static double MEM_CHUNK[DATA_SIZE]; // Buffer de memoria
double *mA, *mB, *mC; // Punteros a matrices

int main(int argc, char *argv[]){ // Función principal
	if (argc < 2){ // Verifica argumentos
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n"); // Instrucción
		return -1;	// Retorna error
	}
    int SZ = atoi(argv[1]); // Tamaño de la matriz
    int n_threads = atoi(argv[2]); // Número de hilos

    pthread_t p[n_threads]; // Arreglo de hilos
    pthread_attr_t atrMM; // Atributos de hilos

	mA = MEM_CHUNK; // Apunta mA a la primera parte de MEM_CHUNK
	mB = mA + SZ*SZ; // Apunta mB a continuación de mA
	mC = mB + SZ*SZ; // Apunta mC a continuación de mB

	llenar_matriz(SZ); // Llena las matrices
	print_matrix(SZ, mA); // Imprime matriz A
	print_matrix(SZ, mB); // Imprime matriz B

	inicial_tiempo(); // Inicializa el conteo de tiempo
	pthread_mutex_init(&MM_mutex, NULL); // Inicializa el mutex
	pthread_attr_init(&atrMM); // Inicializa los atributos de hilos
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE); // Configura atributo para join

    for (int j=0; j<n_threads; j++){ // Crea hilos
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); // Reserva estructura
		datos->idH = j; // Asigna ID del hilo
		datos->nH  = n_threads; // Número de hilos
		datos->N   = SZ; // Tamaño de matriz
        pthread_create(&p[j],&atrMM,mult_thread,(void *)datos); // Crea hilo
	}

    for (int j=0; j<n_threads; j++) // Espera hilos
        pthread_join(p[j],NULL); // Une hilo al principal
	final_tiempo(); // Muestra tiempo de ejecución
	
	print_matrix(SZ, mC); // Imprime matriz C

	pthread_attr_destroy(&atrMM); // Destruye atributos de hilo
	pthread_mutex_destroy(&MM_mutex); // Destruye el mutex
	pthread_exit (NULL); // Termina programa
}