# Taller 6 - Evaluación de Rendimiento de Multiplicación de Matrices

## Autor
Daniel Castro

## Materia
Sistemas Operativos

## Descripción
Este proyecto implementa la multiplicación de matrices cuadradas \(N \times N\) utilizando el modelo de hilos POSIX (Pthreads). Se evalúa el tiempo de ejecución del algoritmo clásico de multiplicación de matrices distribuyendo el trabajo en múltiples hilos. El proyecto incluye tres implementaciones diferentes:

1. **mm_clasico.c**: Implementación clásica de la multiplicación de matrices utilizando múltiples hilos.
2. **mm_transpuesta.c**: Implementación que utiliza la transposición de la matriz para optimizar el acceso a la memoria y mejorar el rendimiento.
3. **Fuente_Evaluacion.c**: Archivo principal que coordina la ejecución y evaluación de las implementaciones de multiplicación de matrices.

## Requisitos
- **Compilador**: gcc
- **Sistema Operativo**: Linux (se ha probado en entornos POSIX)
- **Bibliotecas**: pthreads