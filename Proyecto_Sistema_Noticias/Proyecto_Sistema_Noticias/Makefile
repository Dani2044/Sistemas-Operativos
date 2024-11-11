# Compilador a usar
CC = gcc

# Opciones de compilación: -Wall para mostrar advertencias, -g para incluir información de depuración
CFLAGS = -Wall -g

# Nombres de los ejecutables a generar
TARGETS = publicador suscriptor sistema

# Directorio donde se guardarán los archivos objeto compilados
OBJ_DIR = build

# Regla principal para construir todos los ejecutables
all: $(TARGETS)

# Regla para construir el ejecutable "publicador", depende del archivo objeto
publicador: $(OBJ_DIR)/publicador.o
	$(CC) $(CFLAGS) -o publicador $(OBJ_DIR)/publicador.o

# Regla para construir el ejecutable "suscriptor", depende del archivo objeto
suscriptor: $(OBJ_DIR)/suscriptor.o
	$(CC) $(CFLAGS) -o suscriptor $(OBJ_DIR)/suscriptor.o

# Regla para construir el ejecutable "sistema", depende del archivo objeto
sistema: $(OBJ_DIR)/sistema_comunicacion.o
	$(CC) $(CFLAGS) -o sistema $(OBJ_DIR)/sistema_comunicacion.o

# Regla general para compilar archivos fuente .c a archivos objeto .o en el directorio build
# Requiere el archivo de encabezado utils.h
$(OBJ_DIR)/%.o: src/%.c src/utils.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crea el directorio build si no existe antes de compilar
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Limpia archivos generados: ejecutables, objetos, pipes y el directorio de build
clean:
	rm -f $(TARGETS) $(OBJ_DIR)/*.o
	rm -f pipePSC pipeSSC
	rm -rf $(OBJ_DIR)