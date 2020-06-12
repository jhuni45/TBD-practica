## PROCESAMIENTO GOBLAL EN OpenCV
## Estudiante
- Humpire Cutipa, Hayde Luzmila

## Requerimientos:
- FILTROS LINEALES:
  - Filtro de Sobel
  - Filtro de Laplace
  - Filtro de Bordes de Canny
- FILTROS LINEALES ARBITRARIOS:
  - Máscara de perfilado
  - Máscara de derivada
- FILTROS DE MAXIMO, MINIMO Y MEDIANA:
  - Operaciones de máximo local
  - Operaciones de mínimo local
- OPERACIONES DE MORFOLOGIA:
  - Filtro de Erode
  - Filtro de Dilate
  - Filtro de MorphologyEx
- EJEMPLOS:
  - Aplicar Estiramiento
  - Efecto de Transición

### Google Colab:
Para ver los resultados en Google Colab: https://colab.research.google.com/drive/1lhRgsIcqYrz-YbLsYMGsrPeMnHpKKwud?usp=sharing

## EJERCICIOS

### 1. FILTROS LINEALES:
#### 1.1 Filtro de Sobel

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/1-1_Filtro_Sobel.jpg)

### 1.2 Filtro de Laplace

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/1-2_Filtro_Laplace.jpg)

### 1.3 Filtro de Bordes de Canny

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/1-3_Filtro_Canny.jpg)

## 2. FILTROS LINEALES ARBITRARIOS:
### 2.1 Máscara de perfilado

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/2-1_Filtro_Mascara_Perfilado.jpg)

### 2.2 Máscara de derivada
 

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/2-1_Filtro_Mascara_Derivada.jpg)

## 3. FILTROS DE MAXIMO, MINIMO Y MEDIANA:
### 3.1 Operaciones de máximo y mínimo local

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/3-1_Filtro_MaxMin_Estiramiento.jpg)


## 4. OPERACIONES DE MORFOLOGIA:
### 4.1 Filtro de Erode

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/4-1_Filtro_Erode.jpg


### 4.2 Filtro de Dilate

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/4-2_Filtro_Dilate.jpg)


### 4.3 Filtro de MorphologyEx

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/4-3_Filtro_Morfologica.jpg)


## 5. EJEMPLOS:
### 5.1 Aplicar Estiramiento
Ejemplo 1. Aplicar un ajuste (o estiramiento) local del histograma a la imagen img, con ancho dado. El resultado se almacena en res.

- Entrada: 

![](Entrada/imagen1.jpg)


- Salida:

![](Salida/5-1_Filtro_Estiramiento_Local_Histograma.jpg)


### 5.2 Efecto de Transición
Ejemplo 2. Efecto de transición entre dos imágenes (que deben ser de igual tamaño), a través de un suavizado intermedio.

- Entrada: Imagen A

![](Entrada/imagen1.jpg) 

- Entrada: Imagen B

![](Entrada/imagen2.jpg)

- Salida:

![](Salida/5-2_Filtro_Transicion_Dos_Imagenes0.jpg)
![](Salida/5-2_Filtro_Transicion_Dos_Imagenes20.jpg)
![](Salida/5-2_Filtro_Transicion_Dos_Imagenes40.jpg)
![](Salida/5-2_Filtro_Transicion_Dos_Imagenes60.jpg)
![](Salida/5-2_Filtro_Transicion_Dos_Imagenes80.jpg)
![](Salida/5-2_Filtro_Transicion_Dos_Imagenes99.jpg)

