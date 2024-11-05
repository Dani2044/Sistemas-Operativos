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

use strict;
use warnings;

# Ruta del directorio de trabajo actual
my $Path = `pwd`;
chomp($Path);

# Nombres de los ejecutables que se van a ejecutar
my @Nombres_Ejecutables = ("mm_clasico", "mm_transpuesta");

# Tamaños de las matrices a evaluar
my @Size_Matriz = (100, 200, 300, 500, 1000);

# Número de hilos a utilizar en la ejecución
my @Num_Hilos = (1, 2, 4, 8, 16);

# Número de repeticiones para cada combinación de tamaño de matriz y número de hilos
my $Repeticiones = 30;

# Nombre del archivo de salida
my $output_file = "$Path/resultados_promedio.dat";

# Abre el archivo de salida para escribir los resultados
open(my $out_fh, '>', $output_file) or die "No se pudo abrir el archivo $output_file: $!";

# Escribe el encabezado de la tabla en el archivo de salida
print $out_fh "\t\tMáquina x\n";
print $out_fh "\tmm_clasico\t\t\t\t\tmm_transpuesta\n";
print $out_fh "\t1\t2\t4\t8\t16\t1\t2\t4\t8\t16\n";

# Itera sobre cada tamaño de matriz
foreach my $size (@Size_Matriz) {
    print $out_fh "$size\t";  # Escribe el tamaño de la matriz en la primera columna

    # Itera sobre cada ejecutable
    foreach my $ejecutable (@Nombres_Ejecutables) {
        # Itera sobre el número de hilos
        foreach my $hilo (@Num_Hilos) {
            my $total_time = 0;

            # Ejecuta el programa repetidamente y acumula los tiempos
            for (my $i = 0; $i < $Repeticiones; $i++) {
                my $output = `$Path/$ejecutable $size $hilo`;
                
                # Si el programa genera la salida en milisegundos (ejemplo), obtenla del output
                # Verifica si el valor de tiempo está en la salida (asumimos un solo valor de tiempo en ms)
                if ($output =~ /(\d+(\.\d+)?)/) {
                    $total_time += $1;
                } else {
                    die "No se encontró un valor de tiempo en la salida de $ejecutable con tamaño $size y $hilo hilos.";
                }
            }
            
            # Calcula el promedio de tiempo de ejecución
            my $average_time = $total_time / $Repeticiones;
            
            # Escribe el promedio en el archivo
            printf $out_fh "%.2f\t", $average_time;
        }
    }
    
    # Nueva línea después de cada fila de tamaño de matriz
    print $out_fh "\n";
}

# Cierra el archivo de salida
close($out_fh);
print "Resultados promedios guardados en $output_file\n";
