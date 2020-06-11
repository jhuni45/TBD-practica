# IMPLEMENTACIÓN DE FILTROS 

## Preliminares
- Implementar en OpenCV las siguientes operaciones con filtros.
  - Sobel
  - Laplace
  - Canny
  - Filtro Ajuste
  - Filtro Suavizado

## Para ejecutar
Compilación
```bash
# Creamos el makefile que linkee las librerias
cmake .
# Compilamos el código
make
```

## Resultados
Resultados en Colab: https://colab.research.google.com/drive/1L_HurfPhWpiBiCafSYkp7Qt0jCUQ0uGX

### 1. Sobel
- El primer y el segundo parametro son las imagenes 
```
!./global_op -g test1.jpg test2.jpg
```

Entrada:
  
  ![](test1.jpg)

Salida:
 
 ![](sobel.jpg)
 
  
### 2. Laplace
Entrada:

  ![](test2.jpg)
  
Salida:  
  
  ![](laplace.jpg)
  
### 3. Canny
Entrada:
  
  ![](test1.jpg) 
    
Salida:  
   
  ![](canny.jpg)
  

### 4. Filtro Ajustado
Entrada:
  ![](test2.jpg)


Salida:  
   
  ![](filtro_ajuste.jpg)

### 5. Filtro Ajustado
Entrada:
  ![](test1.jpg) ![](test2.jpg)


Salida:  
   
  errores en la salida 

