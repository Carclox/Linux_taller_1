# Linux_taller_1

## Integrantes:
* Carlos S. Rangel | 1005065786
* Valeria Garcia Rodas | 1192801328
---

En este proyecto se incluye el programa <span style="color:red">**resource_mon**</span> lee la información del SO relacionada con:
* Nombre y fabricante de la CPU del sistema
* Número de núcleos y número de hilos (núcleos reales + núcleos virtuales) y el porcentaje de uso de cada hilo

* Cantidad de memoria físisca instalada en el sistema en MB
* Cantidad de memoria de intercambio (swap) en MB del sistema
* Porcentaje de uso de la memoria física instalada
* Porcentaje de uso de la memoria de intercambio

Este programa se ejecuta hasta que el usuario presione la letra **q**, presione **ctrl + c** , o cierre la **tty** en la que se está ejecutando el programa.

La información de la(s) CPU(s) se actualiza e imprime  los datos obtenidos cada segundo y los muestra por interfaz de linea de comandos en una ventana de texto fija.

En el archivo **README.md** en la carpeta **src** se explica el funcionamiento detallado del programa así como las funciones y variables que utiliza para la obtención de información de la CPU.