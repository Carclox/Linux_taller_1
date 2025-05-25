// Incluimos los headers de los módulos
#include "cpuinfo_manip.h" // Si main() necesita algo de aquí
#include "meminfo_manip.h" // Si main() necesita algo de aquí
#include "tui.h" // Ahora tui.h contendrá la declaración de data_processing, monitor_quit, CLEAR, y extern shouldexit

//---------------------------------------//

// Función para detener el programa en segundo plano (manejador de señal)
void sigusr1_handler(int ignore) {
    // Esta función está vacía intencionalmente; solo sirve para interrumpir `sleep`.
}

// Función principal
int main() {
    // Crear un hilo dedicado para la función de monitoreo de 'q'
    thrd_t thr_quit;

    // La función monitor_quit debe estar definida en "tui.c" y su declaración en "tui.h"
    // Ya que thrd_create espera una función de tipo thrd_start_t (int (*)(void* arg)),
    // y monitor_quit cumple con eso.
    if (thrd_create(&thr_quit, monitor_quit, NULL) != thrd_success) {
        fprintf(stderr, "Error al crear el hilo monitor_quit.\n");
        return EXIT_FAILURE;
    }


    // Ejecutar la lógica principal de recolección y gestión de datos en el hilo principal
    // Ahora data_processing está en tui.c, pero se llama desde aquí.
    data_processing();

    printf("Saliendo del programa principal...\n");

    // Enviar una señal para interrumpir cualquier posible `sleep` en otros hilos.
    // Esto es más bien un "último recurso" si la variable atómica no fue suficiente.
    signal(SIGUSR1, sigusr1_handler);
    raise(SIGUSR1); // Envía la señal SIGUSR1 al proceso actual

    // Esperar a que el hilo de monitoreo de 'q' termine
    thrd_join(thr_quit, NULL);

    return EXIT_SUCCESS; // Es buena práctica usar EXIT_SUCCESS
}