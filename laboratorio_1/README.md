# LEER Y EDITAR IMAGEN BMP
## Integrantes
- Basurco Cayllahua, Eduardo Rolando
- Chavez Cruz, Jhunior Kenyi
- Humpire Cutipa, Hayde Luzmila

## Preliminares
- Realizar el algoritmo para la lectura de una imagen BMP *SIN USAR LIBRERIAS*
  - Pruebas con dos imágenes BMP
  - Dos modificaciones distintas
## Aviso
- *SOLO* para la visualización se usó OpenGl
- La lectura de imagen bmp se realizo sin librerias. Se puede observar en esta porción de código

```cpp
bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr ){
    FILE* infile = fopen( filename, "rb" );		// open binary BMP file for reading
    if ( !infile ){
        fprintf( stderr, "Unable to open file: %s\n", filename );
        return false;
    }
    bool fileFormatOK = false;
    int bChar = fgetc( infile );
    int mChar = fgetc( infile );
    printf("Primer byte %c - Segundo byte %c \n", bChar,mChar);
    if ( bChar == 'B' && mChar == 'M' ){
        skipChars( infile, 4 + 2 + 2 + 4 + 4 );
        printf("Hallando en ancho \n");
        NumCols = readLong( infile );
        printf("Hallando el alto \n");
        NumRows = readLong( infile );
        skipChars( infile, 2 );	
        int bitsPerPixel = readShort( infile );
        skipChars( infile, 4 + 4 + 4 + 4 + 4 + 4 );
        if ( NumCols > 0 && NumCols <= 100000 && NumRows > 0 && NumRows <= 100000
                && bitsPerPixel == 24 && !feof( infile )){
            fileFormatOK = true;
        }
    }
 - - - -
 }
 ```
 
 - La reconstrucción de la imágen tambien se hizo sin librerias. Como se observa en la siguiente porción de código.
 
 ```cpp
 unsigned char* cPtr = ImagePtr;
    for ( int i = 0; i < NumRows; i++ ){
        for ( int j = 0; j < NumCols; j++ ){
            *( cPtr + 2 ) = fgetc( infile );
            *( cPtr + 1 ) = fgetc( infile );
            *cPtr = fgetc( infile );
            cPtr += 3;
        }
        int k = 3 * NumCols;
        for ( ; k < GetNumBytesPerRow( NumCols ); k++ ){
            fgetc( infile );
            *( cPtr++ ) = 0;
        }
    }
    if ( feof( infile ) ){
        fclose ( infile );
        fprintf( stderr, "Error: %s.\n", filename );
        return false;
    }
 - - -
 }
 ```

### Compilación y ejecución de código

```terminal
$ g++ imagenbmp.cpp -o test -lGL -lGLU  -lglut -lm
$ ./test <image>
```
Ejemplo
```terminal
$ ./test bugs2.bmp
```

## Pruebas
### Modificación de la imagen BMP 1
- Se hizo la siguiente modificación sobre el puntero a la imagen 
```cpp
    image = new byte [nrows * ncols ];
    byte* BMPptr = BMPimage, *imageptr = image;
    cout << (nrows*ncols) << " 8-bit pixels in image (" <<(nrows*ncols)<< " bytes).\n";
    for ( int row = 0; row <nrows; row++ ){
        for ( int col = 0; col < ncols; col++ ){
            *imageptr++ = 0.30 * BMPimage[0] + 0.59 * BMPimage[1] + 0.11 * BMPimage[2] + 0.5;
            BMPimage += 3;
        }
    }
```
#### Imagen de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/laboratorio_1/bugs2.bmp)
#### Salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/laboratorio_1/imagesgifts/Peek%2010-05-2020%2021-38.gif)


### Modificación de la imagen BMP 2
- Se hizo la siguiente modificación sobre el puntero a la imagen 
```cpp
    image = new byte [nrows * ncols ];
    byte* BMPptr = BMPimage, *imageptr = image;
    cout << (nrows*ncols) << " 8-bit pixels in image (" <<(nrows*ncols)<< " bytes).\n";
    for ( int row = 0; row <nrows; row++ ){
        for ( int col = 0; col < ncols; col++ ){
            *imageptr++ = 0.30 * BMPptr[0] + 0.59 * BMPptr[1] + 0.11 * BMPptr[2] + 0.5;
            BMPptr += 3;
        }
    }
    
```
### Imagen de entrada
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/laboratorio_1/paisaje.bmp)
#### Salida
![](https://github.com/jhuni45/TCG-Laboratorio/blob/master/laboratorio_1/imagesgifts/Peek%2010-05-2020%2021-49.gif)

