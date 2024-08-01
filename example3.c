/*************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 1/08/24
Tema: Sistemas operativos, parte 2
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char *p;
  char *q;
  printf("Address of p = %s\n", p);
  strcpy(p, "Hello, I´m the best in Operating Systems!");
  printf("%s\n", p);
  printf("About to copy\"Goodbye\" to q\n");
  strcpy(q, "Goodbye");
  printf("String copied\n");
  printf("%s\n", q);
  return 0;
}