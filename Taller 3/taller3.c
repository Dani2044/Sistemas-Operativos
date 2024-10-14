/************************************************************************************************
Fecha: 18/10/2024
Autores: Daniel Castro, María Paula Rodríguez, Eliana Cepeda, Daniel Gómez
Materia: Sistemas Operativos
Tema: Tercer Taller - fork()

Descripción:
- Este programa implementa un sistema que recibe dos archivos de texto con arreglos de enteros
  y dos valores enteros que representan el tamaño de dichos arreglos. El programa realiza cálculos 
  mediante procesos hijos creados con `fork()`, que suman los elementos de los arreglos y pasan 
  los resultados al proceso padre mediante pipes. Los cálculos se dividen en tres procesos hijos:
  el primer hijo suma los elementos del primer arreglo, el segundo hijo suma los del segundo 
  arreglo y el tercer hijo suma ambos resultados. Finalmente, el proceso padre muestra la suma 
  total.
  
  La comunicación entre los procesos se realiza usando tuberías (pipes), lo que permite enviar 
  los resultados parciales de cada proceso hijo al proceso padre de forma segura.
************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "taller3.h"

// Función principal que maneja el flujo general del programa
int main(int argc, char* argv[]) {

    // Verificación del número correcto de argumentos (deben ser 5)
    if (argc != 5) {
        fprintf(stderr, "Uso incorrecto: %s N1 archivo00 N2 archivo01\n", argv[0]);
        return EXIT_FAILURE; // Termina si no hay suficientes argumentos
    }

    // Variables que almacenan el tamaño de los arreglos y nombres de los archivos de entrada
    int N1 = atoi(argv[1]);     // Convierte el primer argumento (tamaño del primer arreglo)
    char* archivo00 = argv[2];  // Nombre del primer archivo
    int N2 = atoi(argv[3]);     // Convierte el tercer argumento (tamaño del segundo arreglo)
    char* archivo01 = argv[4];  // Nombre del segundo archivo

    // Declaración de los punteros para los arreglos que serán leídos desde los archivos
    int *arreglo1 = NULL, *arreglo2 = NULL;

    // Leer los arreglos desde los archivos utilizando las funciones definidas
    leer_arreglo(archivo00, &N1, &arreglo1);  // Carga el primer arreglo desde archivo00
    leer_arreglo(archivo01, &N2, &arreglo2);  // Carga el segundo arreglo desde archivo01

    // Creación de pipes para la comunicación entre procesos (3 pipes)
    int fd1[2], fd2[2], fd3[2];  // Declaración de los pipes
    pipe(fd1);  // Primer pipe para comunicación Gran Hijo -> Primer Hijo
    pipe(fd2);  // Segundo pipe para comunicación Segundo Hijo -> Primer Hijo
    pipe(fd3);  // Tercer pipe para comunicación Primer Hijo -> Padre

    // Primer fork: Creación del Gran Hijo
    pid_t pid1 = fork();
    if (pid1 == 0) {  // Código que ejecutará el Gran Hijo
        close(fd1[0]);  // Cierra el extremo de lectura del primer pipe
        int sumaA = suma(arreglo1, N1);  // Calcula la suma de los elementos del primer arreglo
        printf("GranHijo: [%d] Suma del archivo %s = %d\n", getpid(), archivo00, sumaA);
        write(fd1[1], &sumaA, sizeof(sumaA));  // Envía la suma al Primer Hijo a través del pipe
        close(fd1[1]);  // Cierra el extremo de escritura después de enviar el dato
        exit(EXIT_SUCCESS);  // Termina el proceso Gran Hijo
    }

    // Segundo fork: Creación del Segundo Hijo
    pid_t pid2 = fork();
    if (pid2 == 0) {  // Código que ejecutará el Segundo Hijo
        close(fd2[0]);  // Cierra el extremo de lectura del segundo pipe
        int sumaB = suma(arreglo2, N2);  // Calcula la suma de los elementos del segundo arreglo
        printf("SegundoHijo: [%d] Suma del archivo %s = %d\n", getpid(), archivo01, sumaB);
        write(fd2[1], &sumaB, sizeof(sumaB));  // Envía la suma al Primer Hijo a través del pipe
        close(fd2[1]);  // Cierra el extremo de escritura después de enviar el dato
        exit(EXIT_SUCCESS);  // Termina el proceso Segundo Hijo
    }

    // Tercer fork: Creación del Primer Hijo
    pid_t pid3 = fork();
    if (pid3 == 0) {  // Código que ejecutará el Primer Hijo
        close(fd3[0]);  // Cierra el extremo de lectura del tercer pipe
        close(fd1[1]);  // Cierra el extremo de escritura del primer pipe
        close(fd2[1]);  // Cierra el extremo de escritura del segundo pipe

        // Lee las sumas parciales enviadas por el Gran Hijo y el Segundo Hijo
        int sumaA, sumaB;
        read(fd1[0], &sumaA, sizeof(sumaA));  // Lee la suma del Gran Hijo
        read(fd2[0], &sumaB, sizeof(sumaB));  // Lee la suma del Segundo Hijo

        // Calcula la suma total y la imprime
        int total = sumaA + sumaB;
        printf("PrimerHijo: [%d] Suma total de ambos archivos = %d\n", getpid(), total);
        write(fd3[1], &total, sizeof(total));  // Envía la suma total al Padre
        close(fd3[1]);  // Cierra el extremo de escritura del tercer pipe

        // Cierra los extremos de lectura que ya no se utilizarán
        close(fd1[0]);  
        close(fd2[0]);  
        exit(EXIT_SUCCESS);  // Termina el proceso Primer Hijo
    }

    // Código que ejecuta el proceso Padre
    close(fd1[0]);  // Cierra el primer pipe (ya no es necesario)
    close(fd1[1]);  // Cierra el extremo de escritura del primer pipe
    close(fd2[0]);  // Cierra el segundo pipe (ya no es necesario)
    close(fd2[1]);  // Cierra el extremo de escritura del segundo pipe
    close(fd3[1]);  // Cierra el extremo de escritura del tercer pipe

    // El Padre recibe la suma total del Primer Hijo
    int total;
    read(fd3[0], &total, sizeof(total));  // Lee el total enviado por el Primer Hijo
    printf("Padre: [%d] Suma total recibida = %d\n", getpid(), total);
    close(fd3[0]);  // Cierra el extremo de lectura del tercer pipe

    // Espera la finalización de los procesos hijos
    wait(NULL);  // Espera al Gran Hijo
    wait(NULL);  // Espera al Segundo Hijo
    wait(NULL);  // Espera al Primer Hijo

    // Libera la memoria asignada dinámicamente a los arreglos
    free(arreglo1);  // Libera la memoria del primer arreglo
    free(arreglo2);  // Libera la memoria del segundo arreglo

    return EXIT_SUCCESS;  // Fin del proceso Padre
}