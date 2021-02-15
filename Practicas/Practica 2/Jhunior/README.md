# FILTROS DE IMÁGENES EN OPENCV 
## Estudiante
- Chavez Cruz, Jhunior Kenyi

## Preliminares
- Implementar filtros de imágenes en OpenCV
  - Filtro de Sobel
  - Filtro de Laplace
  - Filtro de bordes de Canny
  - Operaciones morfológicas compuestas
  - Filtros lineales arbitrarios
  
- Para visualizar todos los resultado ingresar en este link => [Resultados finales](https://github.com/jhuni45/TCG-Laboratorio/tree/master/Practicas/Practica%202/Jhunior/salidas)
## Ejecución
Compilación
```bash
# Creamos el makefile que enlace las librerias
cmake .
# Compilamos el código
make
# Ejecutamos
./DisplayImage <imagen1> <imagen2>
```
## Imágenes de entrada para todos los algoritmos
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/imagenes/pokachu.png)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/imagenes/hotdog.png)

### Pruebas
#### 1. Filtro de Sobel
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/salidas/sobelout.gif)

#### 2. Filtro de Laplace
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/salidas/laplaceout.gif)

#### 3. Filtro de bordes de Canny
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/salidas/arbitrarioout.gif)

#### 4. Operaciones morfológicas compuestas
- Ajuste o estiramiento local

![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/salidas/morfo1out.gif)

- Efecto de transición

![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/salidas/morfo2out.gif)


#### 5. Filtros lineales arbitrarios
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/salidas/arbitrarioout.gif)



