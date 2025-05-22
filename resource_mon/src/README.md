# cpuinfo_manip module

Este modulo esta diseñado para extraer la informacion de la CPu, accediendo al directorio /proc/cpuinfo/, contiene 2 funciones **cpu_info()** y **process_cpu_info()**, las cuales se detallan a continuacion:

## cpu_info()

Esta función se encarga de extraer la información de la CPU que se encuentra en el directorio /proc/cpuinfo/, genera un archivo de salida con el nombre data1.txt y en este archivo se guardan los datos de la CPU, por ultimo el programa imprime el siguiente mensaje: "Información de CPU guardada en data1.txt"

**parametros de entrada:**<br>
No tiene parametros <br>
**Valor de retorno**
* 0 : Indica que la operacion se ejecutó correctamente
* 1 : Se retorna este valor si se detecta un error al crear el archivo de salida data1.txt

**Funcionamiento:** <br>
Apertura del archivo de salida: Se intenta crear el archivo data1.txt con permisos de escritura. Si la operación falla, se muestra un mensaje de error y la función termina con un código de retorno 1.

Apertura del archivo /proc/cpuinfo: Se intenta abrir el archivo de información del procesador. Si la operación tiene éxito:

* Se escribe un encabezado === Información de CPU === en el archivo de salida.
* Se lee línea por línea el contenido de /proc/cpuinfo y se escribe en data1.txt.
* Finalmente, el archivo es cerrado.

Manejo de error: Si /proc/cpuinfo no está accesible, se escribe un mensaje en data1.txt indicando que no fue posible acceder al archivo.

Cierre del archivo de salida: Independientemente del resultado, el archivo data1.txt se cierra adecuadamente antes de que la función termine.

**consideraciones**
/proc/cpuinfo es un archivo virtual en sistemas Linux que proporciona detalles sobre el procesador.

buffer[256] se usa para leer las líneas del archivo, pero si el tamaño de línea supera los 256 caracteres, la información podría truncarse.

## process_cpu_info()

Esta función es la encargada de procesar y filtrar la información de la CPU que se almacena en data1.txt, conserva solo las filas de datos que necesitamos de la CPU, como: nombre del modelo, número de núcleos, numero de procesadores y número de hilos en ejecución. Por ultimo crea una variable de salida tipo append en la que se agregarán los datos de la CPU y los imprime en una ventana de texto.

## meminfo()

Esta función lee la información de la memoria del SO que se encuentra en el directorio /proc/cpuinfo/, genera un archivo de salida llamado data2.txt en donde guarda los datos de la memoria. Al finalizar imprime el texto: "Información de memoria y CPU guardada en data2.txt" y enseguida ejecuta la función **process_memory_info()**

## process_memory_info()

Esta función toma los datos de la memoria que se encuentran en data2.txt, los guarda en un archivo de salida con el nombre mem_input, los escala a MB y posteriormente los imprime en una ventana de texto. En este archivo se encuentran datos como: la cantidad de memoria RAM del SO, la cantidad de memoria disponible, cantidad de memoria swap total y el swap libre.

