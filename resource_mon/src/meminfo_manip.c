#include "meminfo_manip.h"


int meminfo(FILE *output_data2_file) {
    /*
    Esta función accede a la información de la memoria a través de /proc/meminfo/
    y escribe el contenido directamente en el archivo apuntado por 'output_data2_file'.
    */
    FILE *meminfo_proc;
    char buffer[256];

    // Verificar si el apuntador al archivo de salida es válido
    if (output_data2_file == NULL) {
        perror("Error: El apuntador al archivo de salida para meminfo es NULL.");
        return 1;
    }

    // Leer información de memoria de /proc/meminfo
    meminfo_proc = fopen("/proc/meminfo", "r");
    if (meminfo_proc != NULL) {
        fprintf(output_data2_file, "=== Información de Memoria ===\n");
        while (fgets(buffer, sizeof(buffer), meminfo_proc) != NULL) {
            fprintf(output_data2_file, "%s", buffer);
        }
        fclose(meminfo_proc);
    } else {
        fprintf(output_data2_file, "No se pudo acceder a /proc/meminfo\n");
    }

    // No se cierra 'output_data2_file' aquí, se deja abierto para que main.c lo cierre
    return 0;
}

// Función para procesar la información de la memoria desde un archivo y escribir en otro.
// recibe los apuntadores a los archivos de entrada y salida como parámetros.



void process_memory_info(FILE *mem_input_file, FILE *output_report_file) {
    char line[256];
    long long mem_total_kb = 0;
    long long mem_free_kb = 0;
    long long swap_total_kb = 0;
    long long swap_free_kb = 0;

    // Verificar si los apuntadores a los archivos son válidos
    if (mem_input_file == NULL) {
        perror("Error: El apuntador al archivo de entrada de memoria es NULL.");
        return;
    }
    if (output_report_file == NULL) {
        perror("Error: El apuntador al archivo de salida de reporte es NULL.");
        return;
    }

    // Rebovinar el archivo de entrada si es necesario (para múltiples lecturas o si ya fue usado)
    fseek(mem_input_file, 0, SEEK_SET);

    while (fgets(line, sizeof(line), mem_input_file) != NULL) {
        if (strstr(line, "MemTotal:")) {
            sscanf(line, "MemTotal: %lld kB", &mem_total_kb);
        } else if (strstr(line, "MemFree:")) {
            sscanf(line, "MemFree: %lld kB", &mem_free_kb);
        } else if (strstr(line, "SwapTotal:")) {
            sscanf(line, "SwapTotal: %lld kB", &swap_total_kb);
        } else if (strstr(line, "SwapFree:")) {
            sscanf(line, "SwapFree: %lld kB", &swap_free_kb);
        }
    }
    // No se cierra 'mem_input_file' aquí, se deja abierto para que main.c lo cierre

    // --- ¡Cálculos en Megabytes! ---
    // 1 MB = 1024 KB
    double mem_total_mb = (double)mem_total_kb / 1024.0;
    double mem_free_mb = (double)mem_free_kb / 1024.0;
    double mem_used_mb = mem_total_mb - mem_free_mb;
    double mem_usage_percent = (mem_total_mb > 0) ? (double)mem_used_mb / mem_total_mb * 100 : 0.00;

    double swap_total_mb = (double)swap_total_kb / 1024.0;
    double swap_free_mb = (double)swap_free_kb / 1024.0;
    double swap_used_mb = swap_total_mb - swap_free_mb;
    double swap_usage_percent = (swap_total_mb > 0) ? (double)swap_used_mb / swap_total_mb * 100 : 0.00;
    // --- Fin de cálculos en Megabytes ---

    // --- ¡Impresión en Megabytes! ---
    fprintf(output_report_file, "| Memoria Física: %.2f MB Instalada\n", mem_total_mb);
    fprintf(output_report_file, "| Uso de Memoria: %.2f %% (%.2f MB / %.2f MB)\n",
            mem_usage_percent, mem_used_mb, mem_total_mb);
    fprintf(output_report_file, "----------------------------------------\n");
    fprintf(output_report_file, "| Intercambio (Swap): %.2f MB Total\n", swap_total_mb);
    fprintf(output_report_file, "| Uso de Swap: %.2f %% (%.2f MB / %.2f MB)\n",
            swap_usage_percent, swap_used_mb, swap_total_mb);
    fprintf(output_report_file, "----------------------------------------\n");

    // No se cierra 'output_report_file' aquí, se deja abierto para que main.c lo cierre
}