#include<tui.h>

// Función para monitorear la entrada de la tecla 'q' y detener el programa
int monitor_quit(void *arg) {
    struct termios old_termios, new_termios;

    // Obtener la configuración actual del terminal
    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;

    // Deshabilitar el modo canónico (lectura línea por línea) y el eco
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    int c;

    while (!atomic_load(&shouldexit)) {
        if (read(STDIN_FILENO, &c, 1) == 1) {
            if (c == 'q' || c == 'Q') {
                atomic_store(&shouldexit, true);
                break;
            }
        }

        // espacio para orden por ctrl + c No es necesario porque el sistema ya hace uso de esta combinacion

        usleep(100000); // Esperar 100 milisegundos antes de volver a verificar
    }

    // Restaurar la configuración original del terminal
        (STDIN_FILENO, TCSANOW, &old_termios);
    return 0; // La función del hilo debe retornar un entero
}
