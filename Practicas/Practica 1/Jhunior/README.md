# Procesamiento global de imágenes 
## Integrante
- Chavez Cruz, Jhunior Kenyi

## Preliminares
- Ejercicio 1: Transición entre dos imágenes A y B (mismo tamaño y número de canales).
- Ejercicio 2: Histograma unidimensional del nivel de gris de una imagen “a.jpg” en color.
- Ejercicio 3: Histograma bidimensional de los canales (R,G) de una imagen “a.jpg” en color, con 64x64 celdas.
- Ejercicio 4: Transformación gamma
- Ejercicio 5: Ecualización conjunta del histograma a una imagen “a.jpg” en color, usando calcHist y LUT.

### Compilación y ejecución de código

```terminal
$ cmake .
$ make
```
Ejemplo
```terminal
$ ./DisplayImage <image> <image>
```

## Pruebas
### Ejercicio 1

#### Imagenes de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/hotdog.png)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/pokachu.png)

#### Salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/salidas/salida_suma.gif)

### Ejercicio 2
#### Imagen de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/pokachu.png)
#### Salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/salidas/salida_histograma.gif)

### Ejercicio 3
#### Imagen de entrada (dos pruebas)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/hotdog.png)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/pokachu.png)
#### Salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/salidas/salida_bihistograma.gif)

### Ejercicio 4
#### Imagen de entrada 
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/pokachu.png)
#### Salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/salidas/salida_bihistograma.gif)


### Ejercicio 5
#### Imagen de entrada 
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/pokachu.png)
#### Salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%201/Jhunior/salidas/salida_ecualization.gif)





