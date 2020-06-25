#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    int m=90;
    Mat img = imread("imagen2.jpg");
    Mat mapa1(img.size(), CV_32FC1);
    Mat mapa2(img.size(), CV_32FC1);
    for (int y= 0; 
         y<img.size().height; y++)
    for (int x= 0; x<img.size().width; x++) {
        mapa1.at<float>(y, x)= x - x%m + y%m;      // Mapa 1
        mapa2.at<float>(y, x)= y - y%m + x%m;      // Mapa 2  
    }
    Mat resultado;
    remap (img, resultado, mapa1, mapa2, INTER_NEAREST);
    imwrite ( "3_Transformacion_Acristalado_Prueba2_90.jpg", resultado);
    cout<< " Transformación Generada ... \n ";
    return 0;
}