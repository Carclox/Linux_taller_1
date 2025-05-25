// test cpu_info.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "cpuinfo_manip.h" // Asegúrate de que cpu_info y process_cpu_info estén declarados aquí

//-----------------------------//

int main(){
    printf("Iniciando prueba del modulo cpuinfo_manip...\n");

    // archivos de test
    const char *test_data1_filename = "test_data1.txt";
    const char *test_output_filename = "test_datos.txt";

    FILE *test_data1_file = NULL;
    FILE *test_output_file =NULL;


    // prueba de cpu_info

    printf("\n --- probando cpu_info() ---\n");

    test_data1_file = fopen(test_data1_filename, "w+");
    if (test_data1_file == NULL){
        // Corregido: Referencia al archivo de prueba correcto y nombre de la función
        perror("Error al abrir test_data1.txt para cpu_info()");
        return EXIT_FAILURE;
    }
    printf("Llamando a cpu_info() para generar  %s ... \n ", test_data1_filename);
    // CORREGIDO: cpui_nfo -> cpu_info
    int cpuinfo_result = cpu_info(test_data1_file);
    if (cpuinfo_result == 0){
        printf("cpu_info() ejecutado con exito contenido guardado en %s. \n",test_data1_filename);
    }else{
        // CORREGIDO: stdrr -> stderr y nombre de la función
        fprintf(stderr, "Error al ejecutar cpu_info(). codigo de error %d\n",cpuinfo_result);
        fclose(test_data1_file);
        return EXIT_FAILURE;
    }

    // PRUEBA DE process_cpu_info()

    printf("--- probando process_cpu_info() ---\n"); // Añadido \n para mejor formato

    // Ya no es necesario corregir test_oputput_file, ya lo habías corregido en el código anterior
    test_output_file = fopen(test_output_filename, "a");
    if (test_output_file == NULL){
        perror("Error al abrir test_datos.txt para process_cpu_info()");
        fclose(test_data1_file);
        return EXIT_FAILURE;
    }
    printf("llamando a process_cpu_info() para procesar %s y escribir en %s... \n", test_data1_filename,test_output_filename);

    fseek(test_data1_file,0, SEEK_SET);
    process_cpu_info(test_data1_file, test_output_file);
    printf("process_cpu_info() ejecutado con exito. reporte agregado a %s. \n", test_output_filename);

    // cierre de los archivos
    printf("\n --- cerrando archivos --- \n");
    fclose(test_data1_file);
    fclose(test_output_file);


    printf("Archivos cerrados, puede revisar '%s' y '%s'. \n", test_data1_filename, test_output_filename);
    printf("Pueba del modulo cpuinfo_manip finalizada con exito. \n");
    return EXIT_SUCCESS;

}