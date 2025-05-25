# Directorios
BIN_DIR = ./bin/
OBJ_DIR = ./obj/
SRC_DIR = ./src/

# Compilador y Banderas
CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c11

# Fuentes de los ejecutables principales (solo los que están en resource_mon/src/)
RESOURCE_MON_SRC = $(SRC_DIR)resource_mon.c $(SRC_DIR)cpuinfo_manip.c $(SRC_DIR)meminfo_manip.c $(SRC_DIR)tui.c

# Objetos correspondientes a las fuentes principales
RESOURCE_MON_OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(RESOURCE_MON_SRC))

# Ejecutables
RESOURCE_MON_EXEC = $(BIN_DIR)resource_mon

# Definimos la ubicación del Makefile de tests (el "coordinador")
TEST_MAKEFILE_DIR = test/bin/

# Regla por defecto: construye 'all' (ahora llama a resource_mon y a tests)
.PHONY: all
all: resource_mon tests

# Regla para resource_mon
.PHONY: resource_mon
resource_mon: $(RESOURCE_MON_EXEC)

$(RESOURCE_MON_EXEC): $(RESOURCE_MON_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

# Regla para tests - ¡DELEGA LA CONSTRUCCIÓN AL SUBDIRECTORIO COORDINADOR!
.PHONY: tests
tests:
	@echo "Construyendo tests desde $(TEST_MAKEFILE_DIR)..."
	$(MAKE) -C $(TEST_MAKEFILE_DIR) # Esto ejecuta 'make' en el directorio test/bin/

# Regla genérica para compilar archivos .c a .o en la carpeta obj (solo para los .c del SRC_DIR principal)
# Esta regla compila: resource_mon/src/*.c -> resource_mon/obj/*.o
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado: $< -> $@"

# Regla para limpiar (limpia todo el proyecto, incluyendo lo que hacen los tests)
.PHONY: clean
clean:
	@echo "Limpiando..."
	@rm -f $(OBJ_DIR)*.o
	@rm -f $(BIN_DIR)*
	@rmdir $(OBJ_DIR) 2>/dev/null || true
	@rmdir $(BIN_DIR) 2>/dev/null || true
	$(MAKE) -C $(TEST_MAKEFILE_DIR) clean || true # Llama al 'clean' del sub-Makefile de tests
	@echo "Limpieza completa."