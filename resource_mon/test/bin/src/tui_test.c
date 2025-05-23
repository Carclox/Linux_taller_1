#include <signal.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <threads.h>
#include <unistd.h>


#include "tui.h"

int printer() {
    unsigned time = 0;
    while (!atomic_load(&shouldexit)){
        system(CLEAR);
        printf("han pasado %d segundos. \n", time);
        time++;
        sleep(1);
    }
}

void sigusr1_handler(int ignore) {}

int main() {
    thrd_t thr_quit;
    // La función monitor_quit debe estar definida en "tui.h" y "tui.c"
    thrd_create(&thr_quit, monitor_quit, NULL);

    // Ejecutar la lógica principal de recolección y gestión de datos en el hilo principal
    printer();

    printf("Saliendo del programa principal...\n");

    // Enviar una señal para interrumpir cualquier posible `sleep` en otros hilos.
    signal(SIGUSR1, sigusr1_handler);
    raise(SIGUSR1); // Envía la señal SIGUSR1 al proceso actual

    // Esperar a que el hilo de monitoreo de 'q' termine
    thrd_join(thr_quit, NULL);
 
}

