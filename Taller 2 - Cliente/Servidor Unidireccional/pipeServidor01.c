/*****************************************************************************

Fecha:   3/10/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio Fork-Pipe-Name

  - Server unidireccional: Recibe mensajes a través de un archivo FIFO.

*****************************************************************************/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO" // Definición del nombre del archivo FIFO

int main()
{
    int fd; // Descriptor de archivo FIFO
    char readbuf[80]; // Buffer para leer los mensajes del cliente
    char end[10]; // Cadena para detectar el fin de la comunicación
    int to_end; // Indicador de fin de proceso
    int read_bytes; // Almacena el número de bytes leídos

    /* Crear el archivo FIFO si no existe */
    printf("\n >>> INICIO SERVIDOR <<<\n");
    mknod(FIFO_FILE, S_IFIFO | 0640, 0); // Crea un FIFO con permisos de lectura (2) y escritura (4)

    strcpy(end, "end"); // Inicializa la cadena que finaliza la comunicación

    while (1) {
        fd = open(FIFO_FILE, O_RDONLY); // Abre el FIFO en modo lectura
        read_bytes = read(fd, readbuf, sizeof(readbuf)); // Lee los datos del cliente
        readbuf[read_bytes] = '\0'; // Termina la cadena leída con '\0'

        // Imprime el mensaje recibido y su longitud
        printf("Mensaje recibido: \"%s\" y su longitud es %d\n", readbuf, (int)strlen(readbuf));

        to_end = strcmp(readbuf, end); // Compara si el mensaje es "end"

        if (to_end == 0) { // Si el mensaje es "end", cierra el servidor
            close(fd); // Cierra el descriptor de archivo
            break; // Termina el ciclo infinito
        }
    }
    return 0; // Finaliza el programa
}