/*****************************************************************************

Fecha:   3/10/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio Fork-Pipe-Name

  - Cliente unidireccional: Envia mensajes a través de un archivo FIFO.

*****************************************************************************/

#include <stdio.h>
#include <sys/stat.h> // Para gestionar propiedades de archivos
#include <sys/types.h>
#include <fcntl.h> // Para controlar archivos
#include <unistd.h>
#include <string.h> // Para manejo de cadenas de caracteres

#define FIFO_FILE "MYFIFO" // Defición del nombre del archivo FIFO

int main()
{
    int fd; // Descriptor para el archivo FIFO
    int end_process; // Indicador para terminar el proceso
    int stringlen; // Longitud de la cadena de entrada
    char readbuf[80]; // Buffer de 80 caracteres para lectura de la entrada
    char end_str[5]; // Cadena "end" para finalizar

    printf("FIFO_CLIENT: Enviar mensajes de forma infinita, para terminar escriba \"end\"\n");

    fd = open(FIFO_FILE, O_CREAT | O_WRONLY); // Abre el archivo FIFO en modo escritura

    strcpy(end_str, "end"); // Inicializa la cadena de terminación

    // Ciclo infinito para enviar mensajes
    while (1) {
        printf("Ingrese un mensaje: ");
        fgets(readbuf, sizeof(readbuf), stdin); // Lee la entrada del usuario
        stringlen = strlen(readbuf); // Calcula la longitud de la cadena
        readbuf[stringlen - 1] = '\0'; // Ingresa el caracter de final

        end_process = strcmp(readbuf, end_str); // Compara la entrada con "end"

        if (end_process != 0) { // Si no es "end"
            write(fd, readbuf, strlen(readbuf)); // Escribe el mensaje en el FIFO
            printf("Mensaje enviado: \"%s\", longitud: %d\n", readbuf, (int) strlen(readbuf));
        } else {
            write(fd, readbuf, strlen(readbuf)); // Envía el mensaje de cierre
            printf("Mensaje enviado: \"%s\", longitud: %d\n", readbuf, (int) strlen(readbuf));
            close(fd); // Cierra el descriptor del archivo FIFO
            break; // Sale del ciclo
        }
    }
    return 0; // Finaliza el programa
}