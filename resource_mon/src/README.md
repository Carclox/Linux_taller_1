la siguiente estructura corresponde a un proyecto en c

**resource_mon** 
     **bin**
        MAKEFILE
    **obj**
        README.md
    **src**
        Makefile
        cpuinfo_manip.c
        cpuinfo_manip.h
        meminfo_manip.c
        meminfo_manip.h
        resource_mon.c ---> programa principal
        tui.c
        tui.h
        **test**


---
lo que está dentro de asterisco **name** es una carpeta
en la carpeta src estan todos los modulos y sus archivos de encabezado
el modulo principal es "resource_mon" alli esta la funcion principal que ejecuta un bucle que realiza las funcionalidades de los demas. modulos hasta obtener la orden de detenerse.
el modulo cpuinfo_manip accede a los datos de la cpu que estan en el directorio /proc/cpuinfo y crea un archivo de texto que debe actualizarse cada 1 segundo sobreescribiendo la informacion.
el modulo meminfo_manip accede a los datos de la memoria en /proc/meminfo y los guarda en otro archivo de texto que tambien debe actualizarse cada 1 segundo, sobre escribiendo la informacion.
el modulo tui.c corresponde a un modulo interfaz de usuario que se ejecuta en un hilo aparte y esta monitoreando una variable atomica 
que espera la pulsacion de la tecla 'q' o la combinacion 'ctrl + c' o el cierre manual de la terminal de comandos para detener todo el programa.
en la carpeta test solo hay archivos de prueba que se pueden ignorar

---
se necesita la estructura de la funcion principal que ejecuta el bucle y, los demas modulos ya estan construidos, despues de interrumpirse limpia toda la memoria y cierra el programa de forma segura. la idea de la funcion princial es:
inicio
lectura de datos de memoria y cpu
creacion y gestion de archivos de texto
mostrar informacion por pantalla cli
repetir hasta orden de salida

---

la orden de salida se ejecuta en paralelo