#include "cpuinfo_manip.h"


// Las variables globales de nombres de archivo han sido eliminadas de este módulo.

// Función para extraer información de /proc/cpuinfo y escribirla en un archivo.
// Ahora recibe un apuntador al archivo de salida (data1.txt) como parámetro.
int cpu_info(FILE *output_data1_file) {
    /*
    Esta función extrae la información contenida en /proc/cpuinfo/
    y escribe el contenido directamente en el archivo apuntado por 'output_data1_file'.
    */
    FILE *cpuinfo_proc;
    char buffer[256];

    // Verificar si el apuntador al archivo de salida es válido
    if (output_data1_file == NULL) {
        perror("Error: El apuntador al archivo de salida para cpu_info es NULL.");
        return 1;
    }

    // Leer información de CPU de /proc/cpuinfo
    cpuinfo_proc = fopen("/proc/cpuinfo", "r");
    if (cpuinfo_proc != NULL) {
        fprintf(output_data1_file, "\n=== Información de CPU ===\n");
        while (fgets(buffer, sizeof(buffer), cpuinfo_proc) != NULL) {
            fprintf(output_data1_file, "%s", buffer);
        }
        fclose(cpuinfo_proc);
    } else {
        fprintf(output_data1_file, "No se pudo acceder a /proc/cpuinfo\n");
    }

    // No se cierra 'output_data1_file' aquí; se deja abierto para que main.c lo cierre.
    return 0;
}

// Función para procesar la información del CPU desde un archivo
// y escribir el reporte en otro archivo.
// Ahora recibe los apuntadores a los archivos de entrada (data1.txt) y salida (datos.txt) como parámetros.
void process_cpu_info(FILE *cpu_input_file, FILE *output_report_file) {
    char line[256];
    char model_name[128] = "Desconocido";
    int cores = 0;
    int threads_real = 0;
    int threads_virtual = 0;
    bool siblings_found = false;
    bool cores_found = false;

    // Verificar si los apuntadores a los archivos son válidos
    if (cpu_input_file == NULL) {
        perror("Error: El apuntador al archivo de entrada de CPU es NULL.");
        return;
    }
    if (output_report_file == NULL) {
        perror("Error: El apuntador al archivo de reporte de salida es NULL.");
        return;
    }

    // Rebovinar el archivo de entrada si es necesario (para múltiples lecturas o si ya fue usado)
    fseek(cpu_input_file, 0, SEEK_SET);

    while (fgets(line, sizeof(line), cpu_input_file) != NULL) {
        if (strstr(line, "model name")) {
            sscanf(line, "model name\t: %[^\n]", model_name);
        } else if (strstr(line, "siblings")) {
            sscanf(line, "siblings\t: %d", &threads_virtual);
            siblings_found = true;
        } else if (strstr(line, "cpu cores")) {
            sscanf(line, "cpu cores\t: %d", &cores);
            cores_found = true;
        } else if (strstr(line, "core id") && cores_found) {
            // Contar el número de "core id" para determinar hilos reales.
            // Esto asume que "core id" aparece una vez por cada hilo real.
            // Si el archivo ya tiene un "core id" para cada hilo, `threads_real`
            // será el recuento exacto de hilos físicos/reales.
            threads_real++;
        }
    }
    // No se cierra 'cpu_input_file' aquí; se deja abierto para que main.c lo cierre.

    // Imprimir información en el archivo de salida
    fprintf(output_report_file, "----------------------------------------\n");
    fprintf(output_report_file, "| Monitor de Recursos                     |\n");
    fprintf(output_report_file, "----------------------------------------\n");
    fprintf(output_report_file, "| CPU: %s\n", model_name);
    fprintf(output_report_file, "| Núcleos: %d\n", cores);
    fprintf(output_report_file, "| Hilos: Reales %d, Virtuales %d\n", threads_real, threads_virtual);
    fprintf(output_report_file, "----------------------------------------\n");

    // No se cierra 'output_report_file' aquí; se deja abierto para que main.c lo cierre.
}