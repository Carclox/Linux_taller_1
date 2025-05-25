OBJ_DIR = ../../../obj/
# SRC_DIR ya no es necesaria aquí si los .c están en el mismo directorio que el Makefile
# Simplemente se usarán los nombres base de los archivos
# INCLUDE_PATH se ajusta para referenciar desde este mismo directorio
INCLUDE_PATH = -I../../../src/

# Compilador y Banderas
CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c11 $(INCLUDE_PATH)

# Fuentes de los tests que este Makefile debe compilar (solo los nombres de archivo)
# Utilizamos 'notdir' para obtener solo los nombres de archivo sin la ruta.
TEST_SOURCES_BASENAMES = cpuinfo_test.c meminfo_test.c tui_test.c

# Objetos correspondientes a estos fuentes, que irán al OBJ_DIR global
# Utilizamos 'patsubst' para convertir los nombres base a rutas de objeto.
TEST_OBJECTS = $(patsubst %.c,$(OBJ_DIR)%.o,$(TEST_SOURCES_BASENAMES))

# Regla por defecto: construye los objetos de test
.PHONY: all
all: $(TEST_OBJECTS)

# Regla genérica para compilar archivos .c (desde este directorio) a .o (en el directorio obj central)
# La regla de patrón ahora es más simple, esperando que los .c estén en el directorio actual (.).
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado (src/tests): $< -> $@"

# Regla para limpiar los objetos que este Makefile crea
.PHONY: clean
clean:
	@echo "Limpiando objetos de test compilados..."
	@rm -f $(TEST_OBJECTS)
	@echo "Objetos de test limpiados."