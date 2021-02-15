# PROCESAMIENTO GLOBAL EN OpenCV
## Estudiante
- Larraondo Lamchog, Alejandro Jesús

## Requerimientos
```terminal
$ apt install python
$ pip install numpy
$ pip install opencv-python
$ pip install matplotlib
```
## EJERCICIOS

### Ejercicio 1: Suma ponderada de dos imágenes.

- Entrada: Imagen field.jpg y Imagen lake.jpg

![](Input/field.jpg)
![](Input/lake.jpg)

- Salida:

![](Output/ej1.gif)


### Ejercicio 2: Realizar la Transformación Gamma de una imagen.


- Entrada: Imagen field.jpg

![](Input/field.jpg)

- Salida con gamma = 0.3:

![](Output/ej2_1.gif)

- Salida con gamma = 2:

![](Output/ej2_2.gif)

### Ejercicio 3: Calcular el histograma unidimensional del nivel de gris de una imagen “a.jpg” en color. El resultado se escribe en salida debug.

- Entrada: Imagen field.jpg

![](Input/field.jpg)

- Salida:

![](Output/ej3.gif)



### Ejercicio 4: Calcular el histograma bidimensional de los canales (R,G) de una imagen “a.jpg” en color, con 64x64 celdas. El resultado se pinta en una imagen.

### Ejercicio 5: Aplicar una ecualización conjunta del histograma a una imagen “a.jpg” en color, usando calcHist y LUT.

- Entrada: Imagen lake.jpg

![](Input/lake.jpg)

- Salida:

![](Output/ej5.gif)