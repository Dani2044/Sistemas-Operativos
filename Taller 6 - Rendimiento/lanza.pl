#!/usr/bin/perl
#************************************************************************************************
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

# Nombres de los ejecutables que se van a ejecutar
@Nombres_Ejecutables = ("mm_clasico", "mm_transpuesta");

# Tamaños de las matrices a evaluar
@Size_Matriz = (100, 200, 300, 500, 1000);

# Número de hilos a utilizar en la ejecución
@Num_Hilos = (1, 2, 4, 8, 16);

# Número de repeticiones para cada combinación de tamaño de matriz y número de hilos
$Repeticiones = 30;

# Bucle que itera sobre cada tamaño de matriz
foreach $size (@Size_Matriz) {
    # Bucle que itera sobre el número de hilos
    foreach $hilo (@Num_Hilos) {
        # Bucle que itera sobre los ejecutables
        foreach $ejecutable (@Nombres_Ejecutables) {
            # Nombre del archivo donde se almacenarán los resultados
            $file = "$Path/$ejecutable-".$size."-Hilos-".$hilo.".dat";

            # Bucle para repetir la ejecución del programa
            for ($i = 0; $i < $Repeticiones; $i++) {
                # Ejecuta el programa y redirige la salida al archivo correspondiente
                system("$Path/$ejecutable $size $hilo >> $file");
            }
            # Cierra el archivo
            # No se necesita cerrar el archivo manualmente ya que se usa 'system' para redirigir.
        }
    }
}
