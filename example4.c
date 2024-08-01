/*************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 1/08/24
Tema: Sistemas operativos, parte 2
**************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(){
  int n, i, *ptr, sum = 0;
  printf("Enter number of elements: ");
  scanf("%d", &n);
  ptr = (int*) calloc(n, sizeof(int));
  if(ptr == NULL){
    printf("Error! Memory not allocated.\n");
    exit(0);
  }
  printf("Enter elements:\n");
  for(i = 0; i < n; i++){
    scanf("%d", ptr + i);
    sum += *(ptr + i);
  }
  printf("Sum = %d\n", sum);
  free(ptr);
  return 0;
}