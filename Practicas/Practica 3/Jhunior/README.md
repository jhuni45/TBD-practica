# TRANSFORMACIONES AFINES IMÁGENES EN OPENCV 
## Estudiante
- Chavez Cruz, Jhunior Kenyi

## Fecha de entrega
18 de junio 11:44 am

## Preliminares
- Implementar transformaciones afines de imágenes en OpenCV
  - Zoom
  - Flip
  - Rotation
  - Inclinacion
  - Transformación afin
  
- Para visualizar todos los resultado ingresar en este link => [Resultados finales](https://github.com/jhuni45/TCG-Laboratorio/tree/master/Practicas/Practica%203/Jhunior/salidas)
## Ejecución
Compilación
```bash
# Creamos el makefile que enlace las librerias
cmake .
# Compilamos el código
make
# Ejecutamos
./DisplayImage <comando> <imagen1> <valor> (este ultimo valor solo para algunos ejemplos)
# Ejemplos
./DisplayImage -f pokachu.png -1
```
## Imágenes de entrada para todos los algoritmos
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%202/Jhunior/imagenes/pokachu.png)

### Pruebas
#### 1. Transformación ZOOM (2x1)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%203/Jhunior/salidas/zoom2x.png)

#### 2. Transformación FLIP (-1)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%203/Jhunior/salidas/flip.png)

#### 3. Transformación ROTACION (20 grados)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%203/Jhunior/salidas/rotar.png)

#### 4. Transformación INCLINACIÓN (45 grados)
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%203/Jhunior/salidas/inclinacion.png)

#### 5. Transformación AFIN
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/Practicas/Practica%203/Jhunior/salidas/affine.png)
