BIN_DIR = ../../bin/
# Desde test/bin/ hasta resource_mon/bin/
OBJ_DIR = ../../obj/
# Desde test/bin/ hasta resource_mon/obj/
SRC_MAKEFILE_DIR = ./src/
# Directorio donde está el Makefile de compilación de fuentes de test

# Compilador y Banderas (se heredan, pero es bueno tenerlos para claridad o si se ejecutan directamente)
CC = gcc
# CFLAGS y LDFLAGS se usarán cuando este Makefile enlace
CFLAGS = -Wall -Wextra -pthread -std=c11
#LIBS = -lm # Ejemplo: si usas funciones matemáticas

# Objetos que deben ser creados por el Makefile en SRC_MAKEFILE_DIR
# Estos son los .o de los tests que esperamos que el sub-Makefile compile
TESTS_SPECIFIC_OBJS = $(OBJ_DIR)cpuinfo_test.o $(OBJ_DIR)meminfo_test.o $(OBJ_DIR)tui_test.o

# Objetos compartidos que son parte de la librería principal (ya compilados por el Makefile principal)
SHARED_LIB_OBJS = $(OBJ_DIR)cpuinfo_manip.o $(OBJ_DIR)meminfo_manip.o $(OBJ_DIR)tui.o

# Todos los objetos necesarios para los tests
ALL_TEST_OBJS = $(TESTS_SPECIFIC_OBJS) $(SHARED_LIB_OBJS)

# Ejecutables de test
CPUINFO_TEST_EXEC = $(BIN_DIR)cpuinfo_test
MEMINFO_TEST_EXEC = $(BIN_DIR)meminfo_test
TUI_TEST_EXEC = $(BIN_DIR)tui_test

# Regla por defecto: construye los tests
.PHONY: all
all: tests

# Regla para construir los tests:
# Primero, llama al Makefile en src/ para que compile los .o
# Luego, construye los ejecutables de test en este nivel
.PHONY: tests
tests: $(ALL_TEST_OBJS) $(CPUINFO_TEST_EXEC) $(MEMINFO_TEST_EXEC) $(TUI_TEST_EXEC)

# Regla para asegurarse de que los .o de los tests se compilen
$(ALL_TEST_OBJS):
	@echo "Delegando compilación de .o de tests a $(SRC_MAKEFILE_DIR)..."
	$(MAKE) -C $(SRC_MAKEFILE_DIR) # Llama a 'make' en el subdirectorio src/

# Reglas para enlazar los ejecutables de test
$(CPUINFO_TEST_EXEC): $(OBJ_DIR)cpuinfo_test.o $(SHARED_LIB_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

$(MEMINFO_TEST_EXEC): $(OBJ_DIR)meminfo_test.o $(SHARED_LIB_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

$(TUI_TEST_EXEC): $(OBJ_DIR)tui_test.o $(SHARED_LIB_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

# Regla de limpieza para este nivel (llama al clean de src/ y luego limpia ejecutables aquí si es necesario)
.PHONY: clean
clean:
	@echo "Limpiando tests..."
	$(MAKE) -C $(SRC_MAKEFILE_DIR) clean || true # Llama al 'clean' del sub-Makefile de fuentes de test
	@rm -f $(CPUINFO_TEST_EXEC) $(MEMINFO_TEST_EXEC) $(TUI_TEST_EXEC)
	@echo "Limpieza de ejecutables de test completa."