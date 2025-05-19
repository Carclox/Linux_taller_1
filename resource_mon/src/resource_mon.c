//#include<resource_mon.h>
/*
Seccion 1 encabezados
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <threads.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h> // Para la manipulación del terminal
#include<string.h>

//---------------------------------------//
/*
seccion de definiciones
*/

// Definiciones necesarias para bloque de actualizacion de ventana grafica
// van en esta seccion porque la funcion de simulacion de ventana no esta implementada aparte
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
// ----------------------------------------------------- //
/*
Seccion de declaracion de variables
*/

// Variable global para la bandera de salida
atomic_bool shouldexit = ATOMIC_VAR_INIT(false);
// Variables globales con los nombres de los archivos 

extern const char *mem_file;
extern const char *cpu_file;
//extern const char *output_file;
const char *output_file = "datos.txt"; 

// ---------------------------------------------------- //

/*
Seccion de declaracion y prototipado de funciones
*/

// funcion que recopila todo el proceso de tratamiento de datos
void data_processing() {
    unsigned counter = 0;  /// verificar utilidad

    while (!atomic_load(&shouldexit)) {
        //limpiar la terminal
        system(CLEAR);

        // Generar los archivos de información
        cpu_info();
        meminfo();

        // Procesar la información y escribir en datos.txt
        // Asegurarse de que el archivo datos.txt esté vacío antes de escribir la nueva información
        // abrir el archivo en modo escritira 'w' y borrar todo lo que este ahi, esto porque las funciones de gestion de datos lo abren en modo append
        FILE *output_clear = fopen(output_file, "w");
        if (output_clear != NULL) {
            fclose(output_clear);
        }

        // procesar la informacion relevante y generar el archivo principal
        process_cpu_info();
        process_memory_info();

        // Simular la lectura y visualización del archivo datos.txt, el archivo se abre en modo lectura 'r'
        FILE *output_read = fopen(output_file, "r");
        if (output_read != NULL) {
            char line[256];
            while (fgets(line, sizeof(line), output_read) != NULL) {
                printf("%s", line);
            }
            fclose(output_read);
        } else {
            perror("Error al abrir datos.txt para lectura y visualización");
        }

        sleep(1); // Simulación de la tarea principal
        counter++;
    }

    printf("Procesamiento de datos terminado.\n");
}

// funcion para detener el programa (manejador de señal)
void sigusr1_handler(int ignore) {}


// funcion principal

int main() {
    // Crear un hilo dedicado para la función de monitoreo de 'q'
    thrd_t thr_quit;
    thrd_create(&thr_quit, monitor_quit, NULL);

    // Ejecutar la lógica principal de recolección y gestión de datos en el hilo principal
    data_processing();

    printf("Saliendo del programa principal...\n");

    // Enviar una señal para interrumpir cualquier posible sleep en otros hilos (incluido el hilo de monitor_quit si estuviera en un usleep largo)
    signal(SIGUSR1, sigusr1_handler);
    raise(SIGUSR1);

    // Esperar a que el hilo de monitoreo de 'q' termine
    thrd_join(thr_quit, NULL); // Podemos pasar NULL si no necesitamos el valor de retorno

    return 0;
}

// ----------------------------------------------------  //
