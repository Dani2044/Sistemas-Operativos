/************************************************************************************************
Fecha: 31/10/2024
Autor: Daniel Castro
Materia: Sistemas Operativos
Tema: Taller 6 - Evaluación de rendimiento
Descripción:
	Este programa realiza la multiplicación de matrices cuadradas N×NN×N empleando el modelo
	de hilos POSIX (Pthreads) y evalúa el tiempo de ejecución del algoritmo clásico de 
	multiplicación de matrices distribuyendo el trabajo en múltiples hilos
************************************************************************************************/

#include <stdio.h> // Para entradas y salidas estándar
#include <pthread.h> // Para manejo de hilos y sincronización
#include <unistd.h> // Para llamadas al sistema como fork()
#include <stdlib.h> // Para uso de funciones básicas
#include <time.h> // Para manejo de tiempo
#include <sys/time.h> // Para medición de tiempos

#define DATA_SIZE (1024*1024*64*3) // Tamaño del buffer de datos

pthread_mutex_t MM_mutex; // Mutex para sincronización de hilos
static double MEM_CHUNK[DATA_SIZE]; // Buffer de memoria
double *mA, *mB, *mC; // Punteros a matrices

struct parametros{ // Estructura para parámetros de hilos
	int nH; // Número de hilos
	int idH; // ID del hilo
	int N; // Tamaño de la matriz
};

struct timeval start, stop; // Variables para tiempos

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