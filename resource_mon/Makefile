# Directorios
BIN_DIR = ./bin/
OBJ_DIR = ./obj/
SRC_DIR = ./src/

# Compilador y Banderas
CC = gcc
CFLAGS = -Wall -Wextra -pthread -std=c11 # -pthread es crucial para atomic_load/store y tui.h puede requerir un C más moderno
#LDFLAGS = -L. # Si tienes alguna librería personalizada en el directorio actual, si no, puedes quitarlo
#LIBS = -lm # Ejemplo: si usas funciones matemáticas

# Fuentes de los ejecutables principales y de test
RESOURCE_MON_SRC = $(SRC_DIR)resource_mon.c $(SRC_DIR)cpuinfo_manip.c $(SRC_DIR)meminfo_manip.c $(SRC_DIR)tui.c
TESTS_SRCS = $(SRC_DIR)cpuinfo_test.c $(SRC_DIR)meminfo_test.c $(SRC_DIR)tui_test.c

# Objetos correspondientes a las fuentes
RESOURCE_MON_OBJS = $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(RESOURCE_MON_SRC))
TESTS_OBJS_CPUINFO = $(OBJ_DIR)cpuinfo_test.o $(OBJ_DIR)cpuinfo_manip.o
TESTS_OBJS_MEMINFO = $(OBJ_DIR)meminfo_test.o $(OBJ_DIR)meminfo_manip.o
TESTS_OBJS_TUI = $(OBJ_DIR)tui_test.o $(OBJ_DIR)tui.o
# Suponiendo que tui_manip.c contiene funciones relacionadas con tui_test

# Ejecutables
RESOURCE_MON_EXEC = $(BIN_DIR)resource_mon
CPUINFO_TEST_EXEC = $(BIN_DIR)cpuinfo_test
MEMINFO_TEST_EXEC = $(BIN_DIR)meminfo_test
TUI_TEST_EXEC = $(BIN_DIR)tui_test

# Regla por defecto: construye 'all'
.PHONY: all
all: $(RESOURCE_MON_EXEC) $(CPUINFO_TEST_EXEC) $(MEMINFO_TEST_EXEC) $(TUI_TEST_EXEC)

# Regla para resource_mon
.PHONY: resource_mon
resource_mon: $(RESOURCE_MON_EXEC)

$(RESOURCE_MON_EXEC): $(RESOURCE_MON_OBJS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

# Regla para tests
.PHONY: tests
tests: $(CPUINFO_TEST_EXEC) $(MEMINFO_TEST_EXEC) $(TUI_TEST_EXEC)

$(CPUINFO_TEST_EXEC): $(TESTS_OBJS_CPUINFO)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

$(MEMINFO_TEST_EXEC): $(TESTS_OBJS_MEMINFO)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

$(TUI_TEST_EXEC): $(TESTS_OBJS_TUI) $(OBJ_DIR)cpuinfo_manip.o $(OBJ_DIR)meminfo_manip.o # Agregamos estas dependencias si el test de TUI depende de ellas
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $^ -o $@ $(LIBS)
	@echo "Construido: $@"

# Regla genérica para compilar archivos .c a .o en la carpeta obj
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compilado: $< -> $@"

# Regla para limpiar
.PHONY: clean
clean:
	@echo "Limpiando..."
	@rm -f $(OBJ_DIR)*.o
	@rm -f $(BIN_DIR)*
	@rmdir $(OBJ_DIR) 2>/dev/null || true
	@rmdir $(BIN_DIR) 2>/dev/null || true
	@echo "Limpieza completa."
