#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
void transformacion_perspectiva(char* file){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }
    double w= input_image1.size().width, h= input_image1.size().height;
    Mat pt1(1, 4, CV_32FC2); // Cuatro puntos en el origen
    pt1.at<Vec2f>(0,0)= Vec2f(0, 0);
    pt1.at<Vec2f>(0,1)= Vec2f(w, 0);
    pt1.at<Vec2f>(0,2)= Vec2f(w, h);
    pt1.at<Vec2f>(0,3)= Vec2f(0, h);
    Mat pt2(1, 4, CV_32FC2); // Cuatro puntos en el destino
    pt2.at<Vec2f>(0,0)= Vec2f(w*0.3, 0);
    pt2.at<Vec2f>(0,1)= Vec2f(w*0.7, 0);
    pt2.at<Vec2f>(0,2)= Vec2f(w, h);
    pt2.at<Vec2f>(0,3)= Vec2f(0, h);
    Mat c= getPerspectiveTransform(pt1, pt2);
    Mat resultado;
    warpPerspective(input_image1, resultado, c, input_image1.size());
    imwrite( "warperspective.jpg", resultado );
}

void remap_image(char* file,int m){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }
    Mat mapa1(input_image1.size(), CV_32FC1);
    Mat mapa2(input_image1.size(), CV_32FC1);
    for (int y= 0; y<input_image1.size().height; y++)
    for (int x= 0; x<input_image1.size().width; x++) {
    mapa1.at<float>(y, x)= x+rand()%(2*m+1) - m; // Mapa 1
    mapa2.at<float>(y, x)= y+rand()%(2*m+1) - m; // Mapa 2
    }
    Mat resultado;
    remap(input_image1, resultado, mapa1, mapa2, INTER_NEAREST);
    imwrite( "remap.jpg", resultado );
}

void transformacion_acristalada(char* file,int m){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }
    Mat mapa1(input_image1.size(), CV_32FC1);
    Mat mapa2(input_image1.size(), CV_32FC1);
    for (int y= 0; y<input_image1.size().height; y++)
    for (int x= 0; x<input_image1.size().width; x++) {
    mapa1.at<float>(y, x)= x - x%m + y%m; // Mapa 1 cambiado
    mapa2.at<float>(y, x)= y - y%m + x%m; // Mapa 2 cambiado
    }
    Mat resultado;
    remap(input_image1, resultado, mapa1, mapa2, INTER_NEAREST);
    imwrite( "acristalado.jpg", resultado );
}

int main(int argc, char **argv)
{
    transformacion_perspectiva(argv[1]);
    remap_image(argv[2],45);
    transformacion_acristalada(argv[1],69);
    return 0;
}