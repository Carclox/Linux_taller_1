#include<meminfo_manip.h>

int meminfo() {
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

    printf("Información de memoria y CPU guardada en data2.txt\n");
    return 0;
}


