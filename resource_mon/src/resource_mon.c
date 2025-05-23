#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <threads.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h> // Para la manipulación del terminal
#include <string.h>

// Incluimos los headers de los módulos
#include "cpuinfo_manip.h"
#include "meminfo_manip.h"
#include "tui.h" // Contiene la función monitor_quit

//---------------------------------------//
/*
Sección de definiciones
*/

// Definiciones para limpiar la terminal
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
// ----------------------------------------------------- //
/*
Sección de declaración de variables globales
*/

// Variable global para la bandera de salida. Esta sí es apropiada como global.
atomic_bool shouldexit = ATOMIC_VAR_INIT(false);
// ---------------------------------------------------- //

/*
Sección de declaración y prototipado de funciones
*/




// Función que recopila todo el proceso de tratamiento de datos
void data_processing() {
    // Nombres de archivos ahora como variables locales y descriptivas
    const char *mem_data_filename = "data2.txt";
    const char *cpu_data_filename = "data1.txt";
    const char *final_output_filename = "datos.txt";

    // Punteros a los archivos que se abrirán y cerrarán en este scope
    FILE *mem_data_file = NULL;
    FILE *cpu_data_file = NULL;
    FILE *final_output_file = NULL;

    while (!atomic_load(&shouldexit)) {
        system(CLEAR); // Limpiar la terminal

        // --- Apertura y manejo de archivos para la iteración actual --- //

        // 1. Abrir data2.txt para la información de memoria
        // Usamos "w+" para crear/truncar y permitir lectura/escritura (necesario para fseek)
        mem_data_file = fopen(mem_data_filename, "w+");
        if (mem_data_file == NULL) {
            perror("Error al abrir data2.txt para escritura en data_processing");
            sleep(1); // Esperar un momento antes de reintentar
            continue; // Saltar a la siguiente iteración del bucle
        }

        // 2. Abrir data1.txt para la información de CPU
        // Asumo que tu cpu_info() también lo necesita en modo "w+" si luego se va a leer.
        cpu_data_file = fopen(cpu_data_filename, "w+");
        if (cpu_data_file == NULL) {
            perror("Error al abrir data1.txt para escritura en data_processing");
            fclose(mem_data_file); // Cerrar el archivo de memoria si falló la CPU
            sleep(1);  // este sleep es unicamente en caso de que no se abran los archivos
            continue;
        }

        // 3. Abrir datos.txt para el reporte final.
        // Lo abrimos en modo "w" para truncar (limpiar) su contenido al inicio de cada ciclo.
        final_output_file = fopen(final_output_filename, "w");
        if (final_output_file == NULL) {
            perror("Error al abrir datos.txt para truncar en data_processing");
            fclose(mem_data_file);
            fclose(cpu_data_file);
            sleep(1);
            continue;
        }
        fclose(final_output_file); // Cerramos inmediatamente para asegurar el truncado

        // --- Llamadas a funciones de módulos, pasando los FILE* ---

        // 1. Generar los archivos intermedios (data1.txt y data2.txt)
        cpu_info(cpu_data_file); // Ahora cpu_info recibe el puntero a data1.txt
        meminfo(mem_data_file);   // Ahora meminfo recibe el puntero a data2.txt

        // 2. Reabrir datos.txt en modo "a" (append) para que las funciones de procesamiento añadan datos
        final_output_file = fopen(final_output_filename, "a");
        if (final_output_file == NULL) {
            perror("Error al reabrir datos.txt para añadir en data_processing");
            fclose(mem_data_file);
            fclose(cpu_data_file);
            sleep(1);
            continue;
        }

        // 3. Procesar la información y escribir en el archivo de salida
        // Asegúrate que estas funciones también reciban los FILE* de entrada y salida
        process_cpu_info(cpu_data_file, final_output_file); // Pasa data1.txt y datos.txt
        process_memory_info(mem_data_file, final_output_file); // Pasa data2.txt y datos.txt

        // Cerrar el archivo de reporte después de que ambas funciones de procesamiento lo usen
        fclose(final_output_file);

        // --- Visualización del reporte final (datos.txt) ---
        FILE *output_read = fopen(final_output_filename, "r");
        if (output_read != NULL) {
            char line[256];
            while (fgets(line, sizeof(line), output_read) != NULL) {
                printf("%s", line);
            }
            fclose(output_read);
        } else {
            perror("Error al abrir datos.txt para lectura y visualización");
        }

        // --- Cierre de archivos al final de la iteración ---
        // ¡Importante! Asegurarse de cerrar todos los archivos abiertos en esta iteración.
        fclose(mem_data_file);
        fclose(cpu_data_file);

        sleep(1); // Simulación de la tarea principal
    }

    printf("Procesamiento de datos terminado.\n");
}

// Función para detener el programa (manejador de señal)
void sigusr1_handler(int ignore) {
    // Esta función está vacía intencionalmente; solo sirve para interrumpir `sleep`.
}

// Función principal
int main() {
    // Crear un hilo dedicado para la función de monitoreo de 'q'
    thrd_t thr_quit;
    // La función monitor_quit debe estar definida en "tui.h" y "tui.c"
    thrd_create(&thr_quit, monitor_quit, NULL);

    // Ejecutar la lógica principal de recolección y gestión de datos en el hilo principal
    data_processing();

    printf("Saliendo del programa principal...\n");

    // Enviar una señal para interrumpir cualquier posible `sleep` en otros hilos.
    signal(SIGUSR1, sigusr1_handler);
    raise(SIGUSR1); // Envía la señal SIGUSR1 al proceso actual

    // Esperar a que el hilo de monitoreo de 'q' termine
    thrd_join(thr_quit, NULL);

    return 0;
}