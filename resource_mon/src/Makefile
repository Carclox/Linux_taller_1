# src/Makefile
# Directorios (relativos a src/)
OBJ_DIR = ../obj # Apunta a la carpeta obj en el nivel superior

# Compilador y Banderas
CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c11

# Fuentes que se compilarán en esta carpeta
SRCS = cpuinfo_manip.c meminfo_manip.c resource_mon.c tui_manip.c # Agrega cualquier otro .c que se encuentre aquí

# Regla por defecto: compilar todos los .c a .o
.PHONY: all
all: $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Regla para compilar un archivo .c a .o en la carpeta obj
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado: $< -> $@"

# Regla para limpiar los .o generados por este Makefile
.PHONY: clean
clean:
	@echo "Limpiando archivos .o en $(OBJ_DIR)..."
	@rm -f $(OBJ_DIR)/cpuinfo_manip.o
	@rm -f $(OBJ_DIR)/meminfo_manip.o
	@rm -f $(OBJ_DIR)/resource_mon.o
	@rm -f $(OBJ_DIR)/tui_manip.o # Agrega los otros .o que este makefile pueda generar
	@echo "Limpieza .o completa."