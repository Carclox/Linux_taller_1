#include "cpuinfo_manip.h"

//const char *cpu_file = "data1.txt";
//const char *output_file; 
//extern const char *output_file; 

int cpu_info(){
    /*
    esta funcion extrae la informacion contenida en /proc/cpuinfo/ y genera un archivo llamado data1.txt
    
    */
    FILE *cpuinfo, *output;
    char buffer[256];

    // crear el archivo de salida
    output = fopen("data1.txt", "w");
    if (output == NULL) {
        perror("Error al crear data1.txt");
        return 1;
    }

    // Leer información de CPU
    cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo != NULL) {
        fprintf(output, "\n=== Información de CPU ===\n");
        while (fgets(buffer, sizeof(buffer), cpuinfo) != NULL) {
            fprintf(output, "%s", buffer);
        }
        fclose(cpuinfo);
    } else {
        fprintf(output, "No se pudo acceder a /proc/cpuinfo\n");
    }

    // Cerrar archivo de salida
    fclose(output);

    //printf("Información de CPU guardada en data1.txt\n");
    return 0;

}


///

// Función para procesar la información del CPU desde data1.txt
void process_cpu_info() {
    FILE *cpu_input, *output;
    char line[256];
    char model_name[128] = "Desconocido";
    int cores = 0;
    int threads_real = 0;
    int threads_virtual = 0;
    bool siblings_found = false;
    bool cores_found = false;

    cpu_input = fopen(cpu_file, "r");
    if (cpu_input == NULL) {
        perror("Error al abrir data1.txt para lectura");
        return;
    }

    while (fgets(line, sizeof(line), cpu_input) != NULL) {
        if (strstr(line, "model name")) {
            sscanf(line, "model name\t: %[^\n]", model_name);
        } else if (strstr(line, "siblings")) {
            sscanf(line, "siblings\t: %d", &threads_virtual);
            siblings_found = true;
        } else if (strstr(line, "cpu cores")) {
            sscanf(line, "cpu cores\t: %d", &cores);
            cores_found = true;
        } else if (strstr(line, "core id") && cores_found) {
            threads_real++;
        }
    }
    fclose(cpu_input);

    output = fopen(output_file, "a"); // Abre en modo append para añadir la info de CPU
    if (output == NULL) {
        perror("Error al abrir datos.txt para escritura");
        return;
    }

    fprintf(output, "----------------------------------------\n");
    fprintf(output, "| Monitor de Recursos                  |\n");
    fprintf(output, "----------------------------------------\n");
    fprintf(output, "| CPU: %s\n", model_name);
    fprintf(output, "| Núcleos: %d\n", cores);
    fprintf(output, "| Hilos: Reales %d, Virtuales %d\n", threads_real, threads_virtual);
    fprintf(output, "----------------------------------------\n");

    fclose(output);
}

