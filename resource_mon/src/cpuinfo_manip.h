#ifndef CPUINFO_MANIP_H
#define CPUINFO_MANIP_H

#include <stdio.h>   // Para FILE y funciones como fopen, fclose, perror, fprintf
#include <string.h>  // Para funciones como strstr, sscanf
#include <stdbool.h> // Para el tipo bool

// Declaración de variables globales
// 'extern' indica que la variable está definida en otro archivo (cpuinfo_manip.c)
//extern const char *cpu_file;
//extern const char *output_file;
const char *cpu_file;
const char *output_file;

// Declaración de funciones
// Estas son las funciones que otros módulos podrán llamar
int cpu_info();
void process_cpu_info();

#endif // CPUINFO_MANIP_H

