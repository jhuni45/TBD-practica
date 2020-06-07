# IMPLEMENTACIÓN EN GPU DE OPERACIONES GLOBALES 
## Integrantes
- Basurco Cayllahua, Eduardo Rolando
- Chavez Cruz, Jhunior Kenyi
- Humpire Cutipa, Hayde Luzmila
- Larraondo Lamchog, Alejandro Jesús 

## Preliminares
- Implementar en GPU las siguientes operaciones Globales.
  - Operador Gama
  - Ecualización de una imagen
  - Una operación aritmética (Ejm: Suma de imágenes)
  - Las operaciones lógicas AND, OR y Negación

## Para ejecutar

```bash
# Creamos el makefile que linkee las librerias
cmake .
# Compilamos el código
make
# Ejecución
./global_op -g | -eq | -not  [image path] [gamma -g]
./global_op -s | -and | -or  [image1 path] [image2 path] [percent -s]
```

## Resultados
### Operador Gama

### Ecualización de una imagen

### Una operación aritmética (Ejm: Suma de imágenes)

### Las operaciones lógicas AND, OR y Negación
#### Operacione lógica AND:
  - Entrada:
  
  ![](Output/imagen1.png) ![](Output/imagen2.png)
  
  - Salida:
  
  ![](Output/and.png)

#### Operacione lógica OR:
  - Entrada:
  
  ![](Output/imagen1.png) ![](Output/imagen2.png)
    
  - Salida:
  
  ![](Output/or.png)
  
#### Operacione lógica Negación:


