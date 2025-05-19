# cpuinfo_manip module

Este modulo esta diseñado para extraer la informacion de la CPu, accediendo al directorio /proc/cpuinfo/, contiene 2 funciones **cpu_info()** y **process_cpu_info()**, las cuales se detallan a continuacion:

## cpu_info()

Esta función se encarga de extraer la información de la CPU que se encuentra en el directorio /proc/cpuinfo/, genera un archivo de salida con el nombre data1.txt y en este archivo se guardan los datos de la CPU, por ultimo el programa imprime el siguiente mensaje: "Información de CPU guardada en data1.txt" luego de esto ejecuta la función **process_cpu_info()**

## process_cpu_info()

Esta función es la encargada de procesar y filtrar la información de la CPU que se almacena en data1.txt, conserva solo las filas de datos que necesitamos de la CPU, como: nombre del modelo, número de núcleos, numero de procesadores y número de hilos en ejecución. Por ultimo crea una variable de salida tipo append en la que se agregarán los datos de la CPU y los imprime en una ventana de texto.

## meminfo()

Esta función lee la información de la memoria del SO que se encuentra en el directorio /proc/cpuinfo/, genera un archivo de salida llamado data2.txt en donde guarda los datos de la memoria. Al finalizar imprime el texto: "Información de memoria y CPU guardada en data2.txt" y enseguida ejecuta la función **process_memory_info()**

## process_memory_info()

Esta función toma los datos de la memoria que se encuentran en data2.txt, los guarda en un archivo de salida con el nombre mem_input, los escala a MB y posteriormente los imprime en una ventana de texto. En este archivo se encuentran datos como: la cantidad de memoria RAM del SO, la cantidad de memoria disponible, cantidad de memoria swap total y el swap libre.

