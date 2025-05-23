#ifndef "TUI_H"
#define "TUI_H"


#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <threads.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h> // Para la manipulación del terminal
#include<string.h>

int monitor_quit(void *arg);


#endif // TUI_H
