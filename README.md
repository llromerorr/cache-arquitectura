# Simulador de Caché - Arquitectura del Computador

El programa es un simulador de caché que permite al usuario especificar el tamaño de la caché, el tamaño de los bloques y el tamaño de los conjuntos. Se implementa en C++ y consta de varios archivos que se describen a continuación:

## Estudiantes
- Luis Romero C.I.: 26.729.561
- Leonardo Moreno C.I.: 28.330.952

## Archivo `main.cpp`

Este archivo contiene la función principal `main`. Al ejecutarse, solicita al usuario información clave sobre la configuración de la memoria caché, como el tamaño de la caché en kilobytes, el tamaño de los bloques en palabras y el tamaño de los conjuntos en bloques. Luego, llama a la función `cache` del archivo `cache.cpp`, proporcionándole los parámetros ingresados por el usuario.

## Archivo `cache.cpp`

Este archivo contiene la implementación de las funciones principales relacionadas con la simulación de la caché. A continuación, se detallan las funciones principales:

### Función `cache`

- La función `cache` realiza cálculos iniciales, como ajustar el tamaño del bloque al siguiente número de potencia de 2 y calcular el número de palabras y bloques en la caché.
- Luego, llama a funciones específicas según el tipo de caché: `cache_directa`, `cache_asociativa` y `cache_conjuntos`.

### Función `cache_directa`

- Simula el comportamiento de una caché directa, mostrando resultados como la dirección de memoria, la etiqueta, el índice y si hubo aciertos o errores en la caché.
- Utiliza un vector para representar la caché y realiza comparaciones para verificar si hay aciertos o errores en la caché.

### Función `cache_asociativa`

- Simula el comportamiento de una caché totalmente asociativa, donde cualquier bloque puede almacenarse en cualquier posición de la caché.
- Utiliza un vector para representar la cola de bloques en la caché y realiza comparaciones para verificar si hay aciertos o errores en la caché.

### Función `cache_conjuntos`

- Simula el comportamiento de una caché asociativa por conjuntos, donde cada conjunto contiene un número fijo de bloques y cada bloque puede estar en cualquier posición dentro de su conjunto.
- Utiliza un vector de vectores para representar los conjuntos y realiza comparaciones para verificar si hay aciertos o errores en el conjunto.

## Archivo `cache.h`

Este archivo es un archivo de encabezado que contiene las declaraciones de las funciones utilizadas en `cache.cpp`. Proporciona una interfaz clara para las funciones implementadas en el archivo de implementación.