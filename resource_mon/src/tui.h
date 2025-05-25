#ifndef TUI_H
#define TUI_H

#include <stdio.h>     // Para FILE, printf, etc.
#include <stdlib.h>    // Para system()
#include <stdatomic.h> // Para atomic_bool
#include <stdbool.h>   // Para bool
#include <threads.h>   // Para thrd_t, thrd_create, thrd_join, thrd_sleep
#include <unistd.h>    // Para sleep, STDIN_FILENO, read
#include <signal.h>    // Para signal, raise
#include <termios.h>   // Para manipulación del terminal (tcgetattr, tcsetattr)
// #include <string.h> // No parece ser necesario en tui.h ni tui.c, si solo se usa en meminfo_manip.c

// Definiciones para limpiar la terminal 
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// DECLARACIÓN de la variable atómica global (¡SOLO DECLARACIÓN AQUÍ!)
extern atomic_bool shouldexit;

// Declaración de funciones del módulo TUI
int monitor_quit(void *arg);
void data_processing(); // Nueva declaración para la función que migramos

#endif // TUI_H