# cpuinfo_manip module

Este modulo esta diseñado para extraer la informacion de la CPU, accediendo al directorio /proc/cpuinfo/, contiene 2 funciones **cpu_info()** y **process_cpu_info()**, las cuales se detallan a continuacion:

## cpu_info(FILE *output_data1_file)

Esta función se encarga de extraer la información de la CPU que se encuentra en el directorio /proc/cpuinfo/, genera (si  no existe) un archivo de salida con el nombre data1.txt y en este archivo se guardan los datos de la CPU.

**parametros de entrada:**<br>
***FILE *output_data1_file*** <br>
recibe el apuntador a un archivo de texto (data1.txt) como parametro
**Parametros de salida**
No tiene parametros de salida

## process_cpu_info(FILE *cpu_input_file, FILE *output_report_file)

Esta función es la encargada de procesar y filtrar la información de la CPU que se almacena en data1.txt, conserva solo las filas de datos que necesitamos de la CPU, como: nombre del modelo, número de núcleos, numero de procesadores y número de hilos en ejecución. Por ultimo, accede a otro archivo de texto (datos.txt) y escribe la informacion relevante en el.
**parametros de entrada:**<br>
***FILE *cpu_input_file*** <br>
recibe el apuntador a un archivo de texto (data1.txt) como parametro.
***FILE *output_report_file***
Apuntador a archivo de salida (datos.txt) con la informacion procesada
**Parametros de salida**
No tiene parametros de salida

# Modulo meminfo_manip
Este modulo se encarga de procesar la informacion de la memoria del sistema accediendo a ella a travez del directorio /proc/meminfo extrae la informacion y luego la filtra y procesa en un archivo de salida.


## meminfo(FILE *output_data2_file)
Esta función lee la información de la memoria del SO que se encuentra en el directorio /proc/cpuinfo/, genera un archivo de salida llamado data2.txt en donde guarda los datos de la memoria. Al finalizar imprime el texto: "Información de memoria y CPU guardada en data2.txt".
**parametros de entrada:**<br>
FILE *output_data2_file
recibe el apuntador a un archivo (data2.txt) donde copia la informacion encontrada en meminfo

**Parametros de salida** <br>
No tiene parametros de salida


## process_memory_info(FILE *mem_input_file, FILE *output_report_file)
Esta función toma los datos de la memoria que se encuentran en data2.txt, los guarda en un archivo de salida con el nombre mem_input, los escala a MB y posteriormente los imprime en el archivo de salida simulando la estructura de una ventana de texto.
**parametros de entrada:**<br>
FILE *mem_input_file,  apuntador al archivo donde esta la infromacion de la memoria
FILE *output_report_file, apuntador a archivo de salida
**Parametros de salida** <br>
No tiene parametros de salida

# modulo tui
Modulo encargado de gestionar la entrada por teclado y la interfaz de usuario
## monitor_quit(void *ar)
esta funcion se encarga de monitorear la entrada por teclado de la letra q, si el susario presion 'q' elprograma se detiene
**parametros de entrada:**<br>
void *arg,  puntero generico que no se utiliza,  

**Parametros de salida** <br>
No tiene parametros de salida


## data_processing()
Esta función recopila todo el rpoceso de tratamiento de informacion relevante, y simula una ventana grafica en la que se muestran los datos requeridos.
**parametros de entrada:**<br>
None
**Parametros de salida** <br>
None
# programa principal resource_mon 
El programa principal main ejecuta toda la logica del monitor de recursos e interfaz de usuario simultaneamente para el que se crea un nuevo hilo de ejecucion.

## void sigusr1_handler(int ignore)
Esta función se utiliza para detener procesos en segundo plano cuando se detecte la interrupcion del programa, está vacia intencionalmente ya que su funcionalidad es unicamente interrumplir usleep() dentro del bloque que controla la terminal para recibir la tecla 'q'

## int main()
Programa principal, primero crea un hilo dedicado a la funcion de monitoreo de 'q', a traves de la funcion monitor_quit, posteriormente realiza el tratamiento y gestion de la informacion a traves de data_processing() hasta que el usuario de la orden de interrumpir la ejecucion, posteriormente interrumpe procesos en otros hilos y retorna "EXIT_SUCCESS"


# test
la seccion test contiene modulos especializados en realizar una prueba de los modulos del programa principal, estos modulos simplemente acceden a los principales y ejecutan las funciones contenidas allí e imprimen en consola un mensaje de error o finalizacion del proceso

## cpuinfo_test
contiene una funcion main() que realiza la prueba de cpuinfo_manip.c (esta funcion no interfiere con el programa principal ni con los demás archivos de test porque no estan enlazados y cada uno tiene su ejecutable independiente)
## meminfo_test
Contiene una funcion main() que accede al modulo meminfo_manip.c y ejecuta las funciones alli contenidas.

## tui_test
Este modulo llama al modulo de interfaz de usuario tui.c para verificar el funcionamiento de la funcion monitor_quit() mientras imprime en pantalla la cantidad de tiempo transcurrido en segundos.