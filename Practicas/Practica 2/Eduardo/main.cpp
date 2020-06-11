#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
void sobel(char* file){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }

    Mat dx,dy,gradiente;
    Sobel(input_image1, dx, CV_32F, 1, 0, -1);
    Sobel(input_image1 , dy, CV_32F, 0, 1, -1);
    pow(dx, 2.0, dx);
    pow(dy, 2.0, dy);
    gradiente= dx+dy;
    sqrt(gradiente, gradiente);
    Mat imgrad;
    gradiente.convertTo(imgrad, CV_8U);
    imwrite( "sobel.jpg", imgrad );
}
void laplace(char* file){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }
    
    Mat lap, suma;
    Laplacian(input_image1, lap, CV_16S);
    input_image1.convertTo(input_image1, CV_16S);
    suma= input_image1 - 0.4*lap;
    suma.convertTo(input_image1, CV_8U);
    imwrite( "laplace.jpg", suma );
}

void canny(char* file){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }
    
    Mat gris, bordes;
    cvtColor(input_image1, gris, CV_BGR2GRAY);
    Canny(gris, bordes, 100, 60);
    imwrite( "canny.jpg", bordes );
}

void MinLocal (Mat entrada, Mat &salida, int ancho, int alto)
{
    erode(entrada, salida, Mat::ones(alto, ancho, CV_8U),
    Point(-1,-1), 1, BORDER_REPLICATE);
}

void MaxLocal (Mat entrada, Mat &salida, int ancho, int alto)
{
    dilate(entrada, salida, Mat::ones(alto, ancho, CV_8U),
    Point(-1,-1), 1, BORDER_REPLICATE);
}

void filtro_ajuste(char* file){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }

    int ancho =5;
    Mat mini, maxi, res;
    int tam= 2*ancho+1; 
    MinLocal(input_image1, mini, tam, tam);
    MaxLocal(input_image1, maxi, tam, tam);
    res= input_image1-mini;
    maxi= maxi-mini;
    divide(res, maxi, res, 255.0);
    imwrite( "filtro_ajuste.jpg", res );
}

void filtro_suavizado(char* file1, char* file2){
    Mat img1= imread( file1, 1 );
    Mat img2= imread( file2, 1 );
    if (img1.empty() || img2.empty()) return;
    Mat int1, int2, res;
    for (int i= 0; i<100; i++) {
        blur(img1, int1, Size(i*4+1, 1));
        blur(img2, int2, Size((99-i)*4+1, 1));
        addWeighted(int1, 1-i/100.0, int2, i/100.0, 0, res);
        if(i = 1) {imwrite("Transicion1.jpg", res);}
        if(i = 25){imwrite("Transicion2.jpg", res);}
        if(i = 50){imwrite("Transicion3.jpg", res);}
        if(i = 75){imwrite("Transicion4.jpg", res);}
        if(i = 99){imwrite("Transicion5final.jpg", res);}
    }
    imwrite("TransicionFinal.jpg", res);
}
int main(int argc, char **argv)
{
    sobel(argv[1]);
    laplace(argv[2]);
    canny(argv[1]);
    filtro_ajuste(argv[2]);
    filtro_suavizado(argv[1],argv[2]);
    return 0;
}