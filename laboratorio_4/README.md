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
- Operacione lógica AND:
  - Entrada:
  ![](Output/image.jpg_binary.png =100x20)
  ![](Output/image.jpg_binary.png =500x1000)
  ![](Output/image2.jpg_binary.png =500x1000)
  
  - Salida:
  ![](Output/image.jpg_binary.png_and.png =50x100)

- Operacione lógica OR:
  - Entrada:
    ![](Output/image.jpg_binary.png =50x100)
    ![](Output/image2.jpg_binary.png =50x100)
    
  - Salida:
  ![](Output/image.jpg_binary.png_or.png =50x100)
  
- Operacione lógica Negación:


