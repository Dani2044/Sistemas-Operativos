/*****************************************************************************

Fecha:   3/10/2024
Autor:   Daniel Felipe Castro Moreno
Materia: Sistemas Operativos

Laboratorio Fork-Pipe-Name

  - Cliente unidireccional

*****************************************************************************/

// Librerias necesarias
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE "MYFIFO" // Definimos el nombre del archivo FIFO
int main()
{
    int fd; // Descriptor de archivo
    int end_process; // Cierre de proceso
    int stringlen; // Longitud de la cadena
    char readbuf[80]; // Buffer de 80 caracteres
    char end_str[5]; // Almacena la cadena "end" para comparación
    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

    fd = open(FIFO_FILE, O_CREAT|O_WRONLY);

    strcpy(end_str, "end");

    // Ciclo infinito para enviar mensajes
    while (1) {
        printf("Enter string: ");
        fgets(readbuf, sizeof(readbuf), stdin);
        stringlen = strlen(readbuf);
        readbuf[stringlen - 1] = '\0';

        end_process = strcmp(readbuf, end_str); 

        if (end_process != 0) {
            write(fd, readbuf, strlen(readbuf));
            printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)    strlen(readbuf));
        } else {
            write(fd, readbuf, strlen(readbuf));
            printf("Sent string: \"%s\" and string length is %d\n", readbuf, (int)    strlen(readbuf));
            close(fd);
            break;
        }
    }
    return 0;
}