#!/usr/bin/perl
#/************************************************************************************************
#Fecha: 31/10/2024
#Autor: Daniel Castro
#Materia: Sistemas Operativos
#Tema: Taller 6 - Evaluación de rendimiento
#Descripción:
#    Este programa realiza la multiplicación de matrices cuadradas N×N empleando el modelo
#    de hilos POSIX (Pthreads) y evalúa el tiempo de ejecución del algoritmo clásico de 
#    multiplicación de matrices distribuyendo el trabajo en múltiples hilos
#************************************************************************************************/

# Obtiene la ruta del directorio de trabajo actual y elimina el salto de línea
$Path = `pwd`;
chomp($Path);

# Nombre del ejecutable que se va a ejecutar
$Nombre_Ejecutable = "MM_ejecutable";

# Tamaños de las matrices a evaluar
@Size_Matriz = ("200","300");

# Número de hilos a utilizar en la ejecución
@Num_Hilos = (1,2);

# Número de repeticiones para cada combinación de tamaño de matriz y número de hilos
$Repeticiones = 2;

# Bucle que itera sobre cada tamaño de matriz
foreach $size (@Size_Matriz) {
    # Bucle que itera sobre el número de hilos
    foreach $hilo (@Num_Hilos) {
        # Nombre del archivo donde se almacenarán los resultados
        $file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

        # Bucle para repetir la ejecución del programa
        for ($i=0; $i<$Repeticiones; $i++) {
            # Ejecuta el programa y redirige la salida al archivo correspondiente
            printf("$Path/$Nombre_Ejecutable $size $hilo \n");
        }
        # Cierra el archivo
        close($file);
        # Incrementa el contador
        $p=$p+1;
    }
}
