#include<cpuinfo_manip.h>

int cpu_info(){
    FILE *cpuinfo, *output;
    char buffer[256];

    // Abrir el archivo de salida
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

    printf("Información de CPU guardada en data1.txt\n");
    return 0;

}

