#include "meminfo_manip.h"


// estas variables ya no deben estar aqui, deben declararse en el archivo main.c
const char *mem_file = "data2.txt";
extern const char *output_file;

int meminfo() {
    /*
    Esta funcion accede a la informacion de la memoria a traves de /proc/meminfo/ y genera un archivo de salida
    .txt llamado data2.txt
    */
    FILE *meminfo, *output;
    char buffer[256];

    // Abrir el archivo de salida
    output = fopen("data2.txt", "w");
    if (output == NULL) {
        perror("Error al crear data2.txt");
        return 1;
    }

    // Leer información de memoria
    meminfo = fopen("/proc/meminfo", "r");
    if (meminfo != NULL) {
        fprintf(output, "=== Información de Memoria ===\n");
        while (fgets(buffer, sizeof(buffer), meminfo) != NULL) {
            fprintf(output, "%s", buffer);
        }
        fclose(meminfo);
    } else {
        fprintf(output, "No se pudo acceder a /proc/meminfo\n");
    }


    // Cerrar archivo de salida
    fclose(output);

    //printf("Información de memoria y CPU guardada en data2.txt\n");
    return 0;
}

// Función para procesar la información de la memoria desde data2.txt
void process_memory_info() {
    FILE *mem_input, *output;
    char line[256];
    long long mem_total_kb = 0;
    long long mem_free_kb = 0;
    long long swap_total_kb = 0;
    long long swap_free_kb = 0;

    mem_input = fopen(mem_file, "r");
    if (mem_input == NULL) {
        perror("Error al abrir data2.txt para lectura");
        return;
    }

    while (fgets(line, sizeof(line), mem_input) != NULL) {
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
    fclose(mem_input);

    output = fopen(output_file, "a"); // Abre en modo append para añadir la info de memoria
    if (output == NULL) {
        perror("Error al abrir datos.txt para escritura");
        return;
    }

    // Actuales calculos en GB, modificar el factor de conversion para obtenerlos en MB
    double mem_total_gb = (double)mem_total_kb / (1024 * 1024);
    double mem_free_gb = (double)mem_free_kb / (1024 * 1024);
    double mem_used_gb = mem_total_gb - mem_free_gb;
    double mem_usage_percent = (mem_total_kb > 0) ? (double)mem_used_gb / mem_total_gb * 100 : 0.00;

    double swap_total_gb = (double)swap_total_kb / (1024 * 1024);
    double swap_free_gb = (double)swap_free_kb / (1024 * 1024);
    double swap_used_gb = swap_total_gb - swap_free_gb;
    double swap_usage_percent = (swap_total_kb > 0) ? (double)swap_used_gb / swap_total_gb * 100 : 0.00;

    fprintf(output, "| Memoria Física: %.2f GB Instalada\n", mem_total_gb);
    fprintf(output, "| Uso de Memoria: %.2f %% (%.2f GB / %.2f GB)\n",
            mem_usage_percent, mem_used_gb, mem_total_gb);
    fprintf(output, "----------------------------------------\n");
    fprintf(output, "| Intercambio (Swap): %.2f GB Total\n", swap_total_gb);
    fprintf(output, "| Uso de Swap: %.2f %% (%.2f GB / %.2f GB)\n",
            swap_usage_percent, swap_used_gb, swap_total_gb);
    fprintf(output, "----------------------------------------\n");

    fclose(output);
}

