# Taller 5 - Máquina virtual
**Fecha:** 24/10/2024  
**Autor:**  
&nbsp;&nbsp;&nbsp;&nbsp;Daniel Castro  

## Descripción General

Este proyecto está dividido en dos partes. La primera aborda la comunicación bidireccional entre un cliente y un servidor usando pipes con nombre (FIFO). La segunda parte utiliza un modelo de productor-consumidor implementado mediante hilos para sincronizar procesos y proteger recursos compartidos utilizando mutex y variables de condición.

## Primera Parte: Comunicación Bidireccional con NamePipe

### Archivos:
- **cliente.c:** Código que envía mensajes al servidor mediante un FIFO y recibe respuestas del servidor.  
- **servidor.c:** Código que recibe mensajes del cliente, los invierte y los reenvía al cliente.  

### Descripción:
El sistema de comunicación bidireccional utiliza un archivo FIFO para que el cliente y el servidor intercambien mensajes. El cliente envía mensajes que el servidor invierte y retorna. El cliente puede finalizar la comunicación enviando la palabra clave "end".

### Compilación y ejecución:
```bash
gcc -o cliente cliente.c
gcc -o servidor servidor.c
./servidor &
./cliente

## Segunda Parte: Productor-Consumidor con Hilos

### Archivos:
- **prod_cons_posix.c:** Implementa el patrón productor-consumidor utilizando hilos de POSIX, sincronización con mutex y variables de condición.

### Descripción:
Se simula un sistema donde múltiples productores incrementan un contador hasta un valor máximo y consumidores decrementan ese contador. La sincronización entre los hilos evita condiciones de carrera mediante mutex y variables de condición.

### Compilación y ejecución:
```bash
gcc -pthread -o prod_cons_posix prod_cons_posix.c
./prod_cons_posix