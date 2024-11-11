/************************************************************************************************
****************************          Funciones Auxiliares          ****************************
************************************************************************************************
Fecha: 31/10/2024
Autor: Daniel Castro - Eliana Cepeda - Maria Paula Rodriguez - Daniel Gonzalez
Materia: Sistemas Operativos
Tema: Taller 6 - Evaluación de rendimiento
Descripción:
    Este archivo contiene las funciones de soporte para la ejecución del programa, incluyendo 
    la inicialización de matrices y la impresión de matrices pequeñas para depuración. 
************************************************************************************************/

#include <stdio.h> // Para entradas y salidas estándar
#include <stdlib.h> // Para uso de funciones básicas
#include <time.h> // Para manejo de tiempo
#include <sys/time.h> // Para medición de tiempos
#include "funciones.h" // Librería propia

extern double *mA, *mB, *mC; // Punteros a matrices
extern struct timeval start, stop; // Variables para tiempos

void llenar_matriz(int SZ){ // Llena las matrices con datos
	srand48(time(NULL)); // Inicializa el generador de números aleatorios
	for(int i = 0; i < SZ*SZ; i++){ // Bucle para llenar matrices
			mA[i] = 1.1*i; // Valor de prueba en mA
			mB[i] = 2.2*i; // Valor de prueba en mB
			mC[i] = 0; // Inicializa mC en 0
		}	
}

void print_matrix(int sz, double *matriz){ // Imprime matriz si es pequeña
	if(sz < 12){ // Solo imprime si la matriz es pequeña
    		for(int i = 0; i < sz*sz; i++){ // Recorre e imprime elementos
     				if(i%sz==0) printf("\n"); // Salto de línea
            		printf(" %.3f ", matriz[i]); // Imprime elemento con 3 decimales
			}	
	}
    printf("\n>-------------------->\n"); // Fin de impresión de matriz
}

void inicial_tiempo(){ // Inicializa el tiempo
	gettimeofday(&start, NULL); // Captura tiempo de inicio
}

void final_tiempo(){ // Calcula y muestra tiempo transcurrido
	gettimeofday(&stop, NULL); // Captura tiempo de fin
	stop.tv_sec -= start.tv_sec; // Calcula segundos
	printf("\n:-> %9.0f µs\n", (double) (stop.tv_sec*1000000 + stop.tv_usec)); // Imprime en µs
}