#!/usr/bin/perl
#************************************************************************************************
#Fecha: 31/10/2024
#Autor: Daniel Castro
#Materia: Sistemas Operativos
#Tema: Taller 6 - Evaluación de rendimiento
#Descripción:
#    Este programa realiza la multiplicación de matrices cuadradas N×N empleando el modelo
#    de hilos POSIX (Pthreads) y evalúa el tiempo de ejecución del algoritmo clásico de 
#    multiplicación de matrices distribuyendo el trabajo en múltiples hilos.
#************************************************************************************************/

# Obtiene la ruta del directorio de trabajo actual y elimina el salto de línea
$Path = `pwd`;
chomp($Path);

# Nombres de los ejecutables que se van a ejecutar
@Nombres_Ejecutables = ("mm_clasico", "mm_transpuesta");

# Tamaños de las matrices a evaluar
@Size_Matriz = (100, 200, 500, 1000, 2000);

# Número de hilos a utilizar en la ejecución
@Num_Hilos = (1, 2, 4, 8, 16);

# Número de repeticiones para cada combinación de tamaño de matriz y número de hilos
$Repeticiones = 30;

# Nombre del archivo para guardar la tabla de resultados
my $archivo_resultados = "$Path/resultados_promedios.dat";

# Abrir archivo de resultados para escribir la tabla final
open(my $fh, '>', $archivo_resultados) or die "No se puede abrir el archivo: $!";

# Imprimir encabezado de la tabla en el archivo
print $fh "\tMáquina x\n";
print $fh "\tmm_clasico\t\t\t\t\t\t\t\t\t\tmm_transpuesta\n";
print $fh "\t1\t\t2\t\t4\t\t8\t\t16\t\t1\t\t2\t\t4\t\t8\t\t16\n";

# Bucle que itera sobre cada tamaño de matriz
foreach my $size (@Size_Matriz) {
    # Línea de la tabla para el tamaño actual
    print $fh "$size\t";
    
    # Bucle que itera sobre los ejecutables
    foreach my $ejecutable (@Nombres_Ejecutables) {
        # Bucle que itera sobre el número de hilos
        foreach my $hilo (@Num_Hilos) {
            my $suma_tiempos = 0;

            # Bucle para repetir la ejecución del programa
            for (my $i = 0; $i < $Repeticiones; $i++) {
                # Ejecuta el programa y captura la salida del tiempo de ejecución
                my $tiempo = `$Path/$ejecutable $size $hilo`;
                
                # Acumular el tiempo para calcular el promedio
                $suma_tiempos += $tiempo;
            }
            # Calcula el promedio del tiempo de ejecución
            my $promedio = $suma_tiempos / $Repeticiones;
            
            # Escribe el promedio en la tabla
            print $fh "$promedio\t";
        }
    }
    print $fh "\n"; # Nueva línea para el siguiente tamaño
}

# Cerrar el archivo de resultados
close($fh);

print "La tabla de promedios ha sido guardada en $archivo_resultados\n";
