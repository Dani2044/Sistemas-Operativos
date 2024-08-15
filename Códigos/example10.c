/*************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 1/08/24
Tema: Sistemas operativos, parte 2
**************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
  int rows, cols, i, j;
  int **matrix;
  
  rows = (int) atof(argv[1]);
  cols = (int) atof(argv[2]);
  
  // Asignación de memoria a la matriz
  matrix = (int **) malloc(rows * sizeof(int *));
  for(i = 0; i < rows; i++){
    matrix[i] = (int *) malloc(cols * sizeof(int));
  }
  
  // Llenado de matriz con valores iniciales
  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      matrix[i][j] = i * j;
    }
  }
  
  // Impresión de matriz
  for(i = 0; i < rows; i++){
    for(j = 0; j < cols; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  
  // Liberación o entrega de memoria al SO
  for(i = 0; i < rows; i++){
    free(matrix[i]);
  }
  free(matrix);
  
  return 0;
}