/************************************************************************************************
****************************               Header Funciones              ************************
************************************************************************************************
Fecha: 31/10/2024
Autor: Daniel Castro
Descripción:
    Declaración de funciones y estructura de parámetros empleada en el programa principal.
************************************************************************************************/

#ifndef FUNCIONES_H
#define FUNCIONES_H

/* Estructura de parámetros */
struct parametros{ // Estructura para parámetros de hilos
	int nH; // Número de hilos
	int idH; // ID del hilo
	int N; // Tamaño de la matriz
};

/* Prototipos de funciones */
void llenar_matriz(int SZ);
void print_matrix(int sz, double *matriz);
void inicial_tiempo();
void final_tiempo();
void *mult_thread(void *variables);

#endif // FUNCIONES_H