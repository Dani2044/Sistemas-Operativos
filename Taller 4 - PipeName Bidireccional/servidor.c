/************************************************************************************************
Fecha: 18/10/2024
Autores: Daniel Castro, María Paula Rodríguez, Eliana Cepeda, Daniel Gómez
Materia: Sistemas Operativos
Tema: Taller 4 - PipeName Bidireccional

Descripción:
        Este programa permite la comunicación bidireccional de un cliente a un servidor usando 
        NamePipes y un archivo FiFO.
************************************************************************************************
        SERVIDOR
************************************************************************************************/

#include <stdio.h> // Para entradas y salidas estándar
#include <sys/stat.h> // Para gestionar propiedades de archivos
#include <sys/types.h> // Para definir tipos de datos como pid_t
#include <fcntl.h> // Para controlar archivos
#include <unistd.h> // Para llamadas al sistema como fork()
#include <string.h> // Para manejo de cadenas de caracteres

#define FIFO_FILE "/tmp/fifo_twoway" // Defición del nombre del archivo FIFO

/* Función principal del servidor */
void reverse_string(char *);
int main() {
   int fd; // Descriptor para el archivo FIFO
   char readbuf[80]; // Buffer para leer los mensajes del cliente
   char end[10]; // Cadena para detectar el fin de la comunicación
   int to_end; // Indicador de fin de proceso
   int read_bytes; // Almacena el número de bytes leídos
   
   /* Crear FIFO si este no existe */
   mkfifo(FIFO_FILE, S_IFIFO|0640); // Crea un FIFO con permisos de lectura (2) y escritura (4)
   strcpy(end, "end"); // Inicializa la cadena que finaliza la comunicación
   fd = open(FIFO_FILE, O_RDWR); // Abre el FIFO en modo lectura
   while(1) {
      read_bytes = read(fd, readbuf, sizeof(readbuf)); // Lee los datos del cliente
      readbuf[read_bytes] = '\0'; // Termina la cadena leída con '\0'
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf)); // Imprime el mensaje recibido y su longitud
      to_end = strcmp(readbuf, end); // Compara la cadena recibida con la de cierre
      
     /* Finalización de la comunicación */
      if (to_end == 0) { // Si el mensaje es "end", cierra el servidor
          close(fd); // Cierra el descriptor de archivo
          break; // Termina el ciclo infinito
      }
    
      reverse_string(readbuf); // Invierte el orden de la cadena
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf)); // Imprime la cadena invertida y su longitud
      write(fd, readbuf, strlen(readbuf)); // Envía mensaje invertido de vuelta al cliente
      /*
      sleep - This is to make sure other process reads this, otherwise this
      process would retrieve the message
      */
      sleep(2);
   }
   return 0; // Finaliza el programa
}

/* Función para invertir el orden de la cadena de caracteres */
/* NOTA: Se elimina limit, pues la comparación se realiza con los iteradores */
void reverse_string(char *str) {
   int last, first; // Iterador en la posición inicial y final
   char temp; // Variable temporal para almacenar un caracter
   last = strlen(str) - 1; // Toma posición final
   first = 0; // Toma posición inicial
   
  /* Itera sobre la cadena, cambiando el caracter en la posición del primer iterador por la del último */
   while (first < last) { // Mientras que no se exceda la mitad de la cadena
      temp = str[first]; // Copia caracter del primer iterador a variable temporal
      str[first] = str[last]; // Copia caracter del segundo iterador al primer iterador
      str[last] = temp; // Copia caracter de la variable temporal al segundo iterador
      first++; // Incrementa primer iterador
      last--; // Disminuye segundo iterador
   }
   return; // Finaliza la función
}
