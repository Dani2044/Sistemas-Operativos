/****************************
Autor: Daniel Castro
Materia: Sistemas operativos
Fecha: 18/07/24
Tema: Introducción al lenguaje C y los entornos
  -Entornos en la web (CLOUD/NUBE)
  -Comandos principales de Linux
  -Programa 0: Hola mundo
****************************/

#include <stdio.h>

int main(int argc, char *argv[]){
  // Variables
  char nombre[] = "Daniel Castro";
  int edad = 19;
  char carrera[] = "Ingeniería de Sistemas";
  int semestre = 4;
  char universidad[] = "Pontificia Javeriana";

  // Imprimir la información del estudiante
  printf("Información del Estudiante\n");
  printf("--------------------------\n");
  printf("Nombre: %s\n", nombre);
  printf("Edad: %d años\n", edad);
  printf("Carrera: %s\n", carrera);
  printf("Semestre: %d\n", semestre);
  printf("Universidad: %s\n", universidad);

  return 0; 
}