// test_meminfo.c
#include <stdio.h>
#include <stdlib.h> // Para EXIT_SUCCESS, EXIT_FAILURE
#include <string.h> // Para strstr, aunque no se usa directamente en este test

#include "meminfo_manip.h"

int main() {
    printf("Iniciando prueba del modulo meminfo_manip...\n");

    const char *test_data2_filename = "test_data2.txt"; // Archivo para simular data2.txt
    const char *test_output_filename = "test_datos.txt"; // Archivo para simular datos.txt

    FILE *test_data2_file = NULL;
    FILE *test_output_file = NULL;

    // --- PRUEBA DE meminfo() ---
    printf("\n--- Probando meminfo() ---\n");
    // Abrir test_data2.txt en modo escritura/lectura
    test_data2_file = fopen(test_data2_filename, "w+");
    if (test_data2_file == NULL) {
        perror("Error al abrir test_data2.txt para meminfo()");
        return EXIT_FAILURE;
    }

    printf("Llamando a meminfo() para generar %s...\n", test_data2_filename);
    int meminfo_result = meminfo(test_data2_file);
    if (meminfo_result == 0) {
        printf("meminfo() ejecutado con exito. Contenido escrito en %s.\n", test_data2_filename);
    } else {
        fprintf(stderr, "Error al ejecutar meminfo(). Codigo de error: %d\n", meminfo_result);
        fclose(test_data2_file);
        return EXIT_FAILURE;
    }

    // --- PRUEBA DE process_memory_info() ---
    printf("\n--- Probando process_memory_info() ---\n");

    // Abrir test_datos.txt en modo append
    test_output_file = fopen(test_output_filename, "a");
    if (test_output_file == NULL) {
        perror("Error al abrir test_datos.txt para process_memory_info()");
        fclose(test_data2_file); // Asegurarse de cerrar el primer archivo
        return EXIT_FAILURE;
    }

    printf("Llamando a process_memory_info() para procesar %s y escribir en %s...\n",
           test_data2_filename, test_output_filename);

    // Asegurarse de que el cursor de test_data2_file esté al inicio para process_memory_info
    // (aunque process_memory_info ya tiene un fseek, es buena práctica aquí también)
    fseek(test_data2_file, 0, SEEK_SET);

    process_memory_info(test_data2_file, test_output_file);
    printf("process_memory_info() ejecutado con exito. Reporte añadido a %s.\n", test_output_filename);

    // --- Cierre de archivos ---
    printf("\nCerrando archivos de prueba...\n");
    fclose(test_data2_file);
    fclose(test_output_file);

    printf("Archivos cerrados. Puede revisar '%s' y '%s'.\n", test_data2_filename, test_output_filename);

    printf("Prueba de meminfo_manip finalizada.\n");
    return EXIT_SUCCESS;
}