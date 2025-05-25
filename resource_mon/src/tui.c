#include "tui.h" // Incluye todas las cabeceras necesarias y las declaraciones
#include "cpuinfo_manip.h" // Necesario para cpu_info y process_cpu_info
#include "meminfo_manip.h" // Necesario para meminfo y process_memory_info

// DEFINICIÓN de la variable atómica global.
// ¡Esta es la ÚNICA DEFINICIÓN de 'shouldexit' en todo el proyecto!
atomic_bool shouldexit = ATOMIC_VAR_INIT(false);

// Función para monitorear la entrada de la tecla 'q' y detener el programa
int monitor_quit(void *arg) {
    (void)arg; // esto hace ignorar la advertencia
    struct termios old_termios, new_termios;

    // Obtener la configuración actual del terminal
    if (tcgetattr(STDIN_FILENO, &old_termios) == -1) {
        perror("tcgetattr failed in monitor_quit");
        atomic_store(&shouldexit, true); // Si falla, mejor salir
        return 1;
    }
    new_termios = old_termios;

    // Deshabilitar el modo canónico (lectura línea por línea) y el eco
    new_termios.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_termios) == -1) {
        perror("tcsetattr new_termios failed in monitor_quit");
        atomic_store(&shouldexit, true); // Si falla, mejor salir
        return 1;
    }

    int c;
    while (!atomic_load(&shouldexit)) {
        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'q' || c == 'Q') {
                atomic_store(&shouldexit, true);
                break;
            }
        }
        // Usar thrd_sleep para C11 threads
        struct timespec ts = { .tv_sec = 0, .tv_nsec = 100 * 1000 * 1000 }; // 100 ms
        thrd_sleep(&ts, NULL);
    }

    // Restaurar la configuración original del terminal
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old_termios) == -1) {
        perror("tcsetattr old_termios failed in monitor_quit");
        // No se puede hacer mucho aquí, el error ya ocurrió
    }
    return 0; // La función del hilo debe retornar un entero
}

// Función que recopila todo el proceso de tratamiento y visualización de datos (MIGRADA desde resource_mon)
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
        mem_data_file = fopen(mem_data_filename, "w+");
        if (mem_data_file == NULL) {
            perror("Error al abrir data2.txt para escritura en data_processing");
            struct timespec ts = { .tv_sec = 1, .tv_nsec = 0 };
            thrd_sleep(&ts, NULL); // Usar thrd_sleep
            continue;
        }

        // 2. Abrir data1.txt para la información de CPU
        cpu_data_file = fopen(cpu_data_filename, "w+");
        if (cpu_data_file == NULL) {
            perror("Error al abrir data1.txt para escritura en data_processing");
            fclose(mem_data_file);
            struct timespec ts = { .tv_sec = 1, .tv_nsec = 0 };
            thrd_sleep(&ts, NULL);
            continue;
        }

        // 3. Abrir datos.txt para el reporte final.
        final_output_file = fopen(final_output_filename, "w");
        if (final_output_file == NULL) {
            perror("Error al abrir datos.txt para truncar en data_processing");
            fclose(mem_data_file);
            fclose(cpu_data_file);
            struct timespec ts = { .tv_sec = 1, .tv_nsec = 0 };
            thrd_sleep(&ts, NULL);
            continue;
        }
        fclose(final_output_file); // Cerramos inmediatamente para asegurar el truncado

        // --- Llamadas a funciones de módulos, pasando los FILE* ---
        cpu_info(cpu_data_file);
        meminfo(mem_data_file);

        // Reabrir datos.txt en modo "a" (append)
        final_output_file = fopen(final_output_filename, "a");
        if (final_output_file == NULL) {
            perror("Error al reabrir datos.txt para añadir en data_processing");
            fclose(mem_data_file);
            fclose(cpu_data_file);
            struct timespec ts = { .tv_sec = 1, .tv_nsec = 0 };
            thrd_sleep(&ts, NULL);
            continue;
        }

        process_cpu_info(cpu_data_file, final_output_file);
        process_memory_info(mem_data_file, final_output_file);

        fclose(final_output_file);

        // --- Visualización del reporte final (datos.txt) --- //
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
        fclose(mem_data_file);
        fclose(cpu_data_file);

        struct timespec ts = { .tv_sec = 1, .tv_nsec = 0 };
        thrd_sleep(&ts, NULL);
    }

    printf("Procesamiento de datos terminado.\n");
}