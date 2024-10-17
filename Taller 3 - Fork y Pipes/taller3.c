/************************************************************************************************
Fecha: 12/10/2024
Autores: Daniel Castro, María Paula Rodríguez, Eliana Cepeda, Daniel Gonzalez
Materia: Sistemas Operativos
Tema: Tercer Taller - fork()

Descripción:
- Este programa implementa un sistema que recibe dos archivos de texto con arreglos de enteros
  y dos valores enteros que representan el tamaño de dichos arreglos. El programa realiza cálculos 
  mediante procesos hijos creados con fork(), que suman los elementos de los arreglos y pasan 
  los resultados al proceso padre mediante pipes. Los cálculos se dividen en tres procesos hijos:
  el primer hijo suma los elementos del primer arreglo, el segundo hijo suma los del segundo 
  arreglo y el tercer hijo suma ambos resultados. Finalmente, el proceso padre muestra la suma 
  total.
  
- La comunicación entre los procesos se realiza usando tuberías (pipes), lo que permite enviar 
  los resultados parciales de cada proceso hijo al proceso padre de forma segura.
************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "taller3.h"

// Función principal que maneja el flujo general del programa
int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Uso incorrecto: %s N1 archivo00 N2 archivo01\n", argv[0]);
        return EXIT_FAILURE;
    }

    int N1 = atoi(argv[1]);
    char *archivo00 = argv[2];
    int N2 = atoi(argv[3]);
    char *archivo01 = argv[4];

    int *arreglo1 = NULL, *arreglo2 = NULL;

    leer_arreglo(archivo00, &N1, &arreglo1);  // Lee el primer archivo
    leer_arreglo(archivo01, &N2, &arreglo2);  // Lee el segundo archivo

    // Crear pipes de forma dinámica
    int (*pipes)[2] = malloc(3 * sizeof(int[2]));
    for (int i = 0; i < 3; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("Error al crear el pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Primer fork
    pid_t primerfork = fork();
    if (primerfork < 0) {
        perror("Error en la ejecución de fork()");
        exit(EXIT_FAILURE);
    }

    // Segundo fork
    pid_t segundofork = fork();
    if (segundofork < 0) {
        perror("Error en la ejecución de fork()");
        exit(EXIT_FAILURE);
    }

    // Segundo Hijo (Calcula sumaB del archivo01)
    if (primerfork > 0 && segundofork == 0) {
        // Calcular la suma del segundo arreglo
        int sumaB = suma(arreglo2, N2);
        write(pipes[1][1], &sumaB, sizeof(sumaB));  // Enviar sumaB al Padre
        close(pipes[1][1]);  // Cerrar extremo de escritura
        printf("SegundoHijo: [%d] Suma del archivo %s = %d\n", getpid(), archivo01, sumaB);
        exit(EXIT_SUCCESS);
    }

    // Gran Hijo (Calcula sumaA del archivo00)
    else if (primerfork == 0 && segundofork == 0) {
        // Calcular la suma del primer arreglo
        int sumaA = suma(arreglo1, N1);
        write(pipes[0][1], &sumaA, sizeof(sumaA));  // Enviar sumaA al Padre
        close(pipes[0][1]);  // Cerrar extremo de escritura
        printf("GranHijo: [%d] Suma del archivo %s = %d\n", getpid(), archivo00, sumaA);
        exit(EXIT_SUCCESS);
    }

    // Primer Hijo (Calcula la suma total de ambos arreglos)
    else if (primerfork == 0 && segundofork > 0) {
        // Leer las sumas desde los pipes de los otros hijos
        int sumaA, sumaB;
        read(pipes[0][0], &sumaA, sizeof(sumaA));  // Leer suma del Gran Hijo
        read(pipes[1][0], &sumaB, sizeof(sumaB));  // Leer suma del Segundo Hijo

        // Sumar ambas sumas
        int suma_total = sumaA + sumaB;

        // Enviar la suma total al proceso Padre
        write(pipes[2][1], &suma_total, sizeof(suma_total));
        close(pipes[2][1]);  // Cerrar extremo de escritura
        printf("PrimerHijo: [%d] Suma total de ambos archivos = %d\n", getpid(), suma_total);
        exit(EXIT_SUCCESS);
    }

    // Proceso Padre (Recibe los cálculos desde los 3 procesos)
    else if (primerfork > 0 && segundofork > 0) {
        // Esperar a los hijos y gran hijo
        wait(NULL);  // Esperar a Primer Hijo
        wait(NULL);  // Esperar a Segundo Hijo
        wait(NULL);  // Esperar a Gran Hijo

        // Declarar variable para almacenar la suma total recibida
        int suma_total_recibida;

        // Leer la suma total calculada por el Primer Hijo
        read(pipes[2][0], &suma_total_recibida, sizeof(suma_total_recibida));  // Leer del Primer Hijo
        printf("Padre: [%d] Suma total recibida del Primer Hijo = %d\n", getpid(), suma_total_recibida);
    }

    // Cerrar pipes
    for (int i = 0; i < 3; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Liberar memoria
    free(arreglo1);
    free(arreglo2);
    free(pipes);

    return EXIT_SUCCESS;
}