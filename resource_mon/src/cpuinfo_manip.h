#ifndef CPUINFO_MANIP_H
#define CPUINFO_MANIP_H

#include <stdio.h>   // Para FILE y funciones como fopen, fclose, perror, fprintf
#include <string.h>  // Para funciones como strstr, sscanf
#include <stdbool.h> // Para el tipo bool

// Declaración de funciones
// Estas son las funciones que otros módulos podrán llamar
int cpu_info(FILE *output_data1_file);
void process_cpu_info(FILE *cpu_input_file, FILE *output_report_file);

#endif // CPUINFO_MANIP_H

