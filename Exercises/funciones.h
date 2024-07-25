/*************************************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 25/07/24
Tema: Entradas y salidas en C
**************************************************/

#include <stdio.h>
#include <math.h>

#ifndef MPI
#define MPI 3.14159265358979323846
#endif

// Variables globales
int a, b, r, h, co, ca, suma, o;
double v1, v2, area, tg;

void fsuma() {
  //Sumar 2 valores que entran por teclado
  printf("Ingrese el primer valor:\n");
  scanf("%d", &a);
  printf("Ingrese el segundo valor:\n");
  scanf("%d", &b);
  suma = a + b;
  printf("La suma de %d + %d = %d.\n", a, b, suma);
}

void farea() {
  //Calcular el área del círculo
  printf("Ingrese el radio:\n");
  scanf("%d", &r);
  area = MPI * pow(r, 2);
  printf("El área del círculo de radio %d es %f.\n", r, area);
}

void fcir() {
  //Calcular el volumen de una circunferencia
  printf("Ingrese el radio:\n");
  scanf("%d", &r);
  v1 = 4 * MPI * pow(r, 3) / 3;
  printf("El volumen de la circunferencia de radio %d es %f.\n", r, v1);
}

void fcono() {
  //Calcular el volumen de un cono
  printf("Ingrese el radio:\n");
  scanf("%d", &r);
  printf("Ingrese la altura:\n");
  scanf("%d", &h);
  v2 = MPI * pow(r, 2) * h / 3;
  printf("El volumen del cono de radio %d es %f.\n", r, v2);
}

void ftg() {
  //Calcular la tangente
  printf("Ingrese el primer cateto:\n");
  scanf("%d", &co);
  printf("Ingrese el segundo cateto:\n");
  scanf("%d", &ca);
  tg = sqrt(pow(co, 2) + pow(ca, 2));
  printf("El valor de la tangente de cateto opuesto %d y cateto adyacente %d es %f.\n", co, ca, tg);
}