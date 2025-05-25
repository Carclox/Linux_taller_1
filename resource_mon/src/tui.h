#ifndef TUI_H
#define TUI_H


#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <threads.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h> // Para la manipulación del terminal
#include<string.h>

// Definiciones para limpiar la terminal
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

extern _Atomic bool shouldexit;

int monitor_quit(void *arg);


#endif // TUI_H
