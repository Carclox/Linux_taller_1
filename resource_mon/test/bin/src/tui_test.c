
#include "tui.h" 


// printer() debe retornar un int, ya que es una función que podría ser usada por thrd_create 
int printer() {
    // La variable 'shouldexit' es externa, definida en resource_mon.c y declarada en tui.h
    extern atomic_bool shouldexit;

    unsigned int time = 0; // Usar unsigned int para evitar warnings si 'time' crece mucho
    while (!atomic_load(&shouldexit)) {
        system(CLEAR); // Asegúrate de que CLEAR esté definido en tui.h
        printf("han pasado %u segundos. \n", time); // Usar %u para unsigned int
        time++;
        // Usar thrd_sleep para C11 threads, es más portable que sleep/usleep
        struct timespec ts = { .tv_sec = 1, .tv_nsec = 0 }; // 1 segundo
        thrd_sleep(&ts, NULL);
    }
    return 0; // Las funciones de hilo deben retornar un int
}

// Handler para la señal SIGUSR1 (puede ser necesario si se usa SIGUSR1 para interrumpir hilos bloqueados)
// Si el objetivo es solo detener el bucle, la variable atómica es más directa.
void sigusr1_handler(int ignore) {
    // Este handler puede estar vacío si solo se usa para interrumpir llamadas a sistema
    // como sleep/read, que podrían bloquearse indefinidamente.
}

int main() {
    thrd_t thr_quit;

    // La función monitor_quit debe estar definida en "tui.c" con la firma int (*)(void *)
    thrd_create(&thr_quit, monitor_quit, NULL);

    // Ejecutar la lógica principal de recolección y gestión de datos en el hilo principal
    printer(); // Esto es el hilo principal corriendo la función printer

    printf("Saliendo del programa principal...\n");

    // Opcional: Enviar una señal para interrumpir cualquier posible `sleep` o `read` en otros hilos.
    // Esto es más un "último recurso" si la variable atómica no es suficiente por bloqueos de E/S.
    // Si la variable atómica 'shouldexit' ya está controlando el bucle de 'monitor_quit',
    // esta señal podría no ser necesaria, o solo para manejar casos de bloqueo inesperado.
    signal(SIGUSR1, sigusr1_handler); // Instalar el handler
    raise(SIGUSR1); // Envía la señal SIGUSR1 al proceso actual

    // Esperar a que el hilo de monitoreo de 'q' termine
    thrd_join(thr_quit, NULL);

    printf("Prueba del modulo TUI finalizada con exito.\n");

    return EXIT_SUCCESS;
}