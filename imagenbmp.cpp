#include <cstdio>
#include <iostream>
#include <GL/glut.h>

using namespace std;

typedef unsigned char byte;
byte* BMPimage;
byte* image;
int nrows, ncols;
int ScreenWidth  = 1024;
int ScreenHeight =  768;

bool LoadBmpFile( const char* filename, int &NumRows, int &NumCols, unsigned char* &ImagePtr );
static short readShort( FILE* infile );
static int readLong( FILE* infile );
static void skipChars( FILE* infile, int numChars );
static inline int GetNumBytesPerRow( int NumCols );

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

    if ( !fileFormatOK ){
        fclose ( infile );
        fprintf( stderr, "Archivo invalido: %s.\n", filename );
        return false;
    }

    ImagePtr = new unsigned char[ NumRows * GetNumBytesPerRow( NumCols ) ];
    if ( !ImagePtr ){
        fclose ( infile );
        fprintf( stderr, "Muy grande %i x %i bitmap: %s.\n",NumRows, NumCols, filename );
        return false;
    }
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
    fclose( infile );
    return true;
}

static inline int GetNumBytesPerRow( int NumCols ){
    return ((3 * NumCols + 2 ) >> 2 ) << 2;
}

short readShort( FILE* infile ){
    unsigned char lowByte, hiByte;
    lowByte = fgetc( infile );
    hiByte = fgetc( infile );

    short ret = hiByte;
    ret <<= 8;
    ret |= lowByte;
    return ret;
}

int readLong( FILE* infile ){
    unsigned char byte0, byte1, byte2, byte3;
    byte0 = fgetc( infile );
    byte1 = fgetc( infile );
    byte2 = fgetc( infile );
    byte3 = fgetc( infile );
    printf("byte 0 %d - byte 1 %d - byte 2 %d - byte 3 %d \n", byte0,byte1,byte2,byte3);

    int ret = byte3;
    ret <<= 8;
    ret |= byte2;
    ret <<= 8;
    ret |= byte1;
    ret <<= 8;
    ret |= byte0;
    printf(" value %d \n",ret );
    return ret;
}

void skipChars( FILE* infile, int numChars ){
    for ( int i = 0; i < numChars; i++ ){
        fgetc( infile );
    }
}

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth(1.0f);
   glEnable(GL_DEPTH_TEST); 
   glDepthFunc(GL_LEQUAL);
   glShadeModel(GL_SMOOTH);   
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  
}

void displayColor( int x, int y, int w, int h, byte* image ){
    glRasterPos2i( x, y );
    glDrawPixels( w, h, GL_RGB, GL_UNSIGNED_BYTE, BMPimage );
}

void displayMonochrome( int x, int y, int w, int h, byte* image ){
    glRasterPos2i( x, y );
    glDrawPixels( w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE, image );
}

void drawText( char *str, int x, int y ) {
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i( x, y );
    while ( *str )
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, *str++ );
}

void display( void ){
    glClear( GL_COLOR_BUFFER_BIT );
    displayMonochrome( 0, 0, ncols, nrows, image );
    displayMonochrome( ncols, 0, ncols, nrows, BMPimage);
    drawText((char*)"IMAGEN ORIGINAL", (ncols/3)+20, (nrows+8));
    drawText((char*)"PRIMER LABORATORIO DE TOPICOS EN GRAFICA", ((ncols/3)+200), (nrows + 20));
    drawText((char*)"IMAGEN MODIFICADA", ((ncols/3) + ncols)-10, (nrows + 5));
    glFlush();
}

void reshape( int w, int h ){
    ScreenWidth = w;
    ScreenHeight = h;
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, w, 0.0, h );
    glViewport( 0, 0, w, h );
}

void initOpenGL( const char *filename, int nrows, int ncols ){
    glutInitDisplayMode( GLUT_RGBA | GLUT_SINGLE );
    ScreenWidth = 2 * ncols;
    ScreenHeight = nrows+40;
    glutInitWindowSize( ScreenWidth, ScreenHeight);
    glutInitWindowPosition( 100, 50 );
    glutCreateWindow( filename );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glutDisplayFunc( display );             
    glutReshapeFunc( reshape );             
}

int main(int argc, char *argv[] ){
    if ( !LoadBmpFile( argv[1], nrows, ncols, BMPimage ) ){
        cout << "Error: no se puede cargar " << argv[1] << endl;
        return -1;
    }
    printf("filas: %d columnas: %d\n",  nrows, ncols);
    image = new byte [nrows * ncols ];
    byte* BMPptr = BMPimage, *imageptr = image;
    cout << (nrows*ncols) << " 8-bit pixels in image (" <<(nrows*ncols)<< " bytes).\n";
    for ( int row = 0; row <nrows; row++ ){
        for ( int col = 0; col < ncols; col++ ){
            *imageptr++ = 0.30 * BMPimage[0] + 0.59 * BMPimage[1] + 0.11 * BMPimage[2] + 0.5;
            BMPimage += 3;
        }
    }
    

    glutInit( &argc, argv );
    initOpenGL( argv[1], nrows, ncols );
    glutMainLoop();
    
    return 0;
}