#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

void MinLocal (Mat entrada, Mat &salida, int ancho, int alto){
    erode(entrada, salida, Mat::ones(alto, ancho, CV_8U), Point(-1,-1), 1, BORDER_REPLICATE);
}
void MaxLocal (Mat entrada, Mat &salida, int ancho, int alto){
    dilate(entrada, salida, Mat::ones(alto, ancho, CV_8U), Point(-1,-1), 1, BORDER_REPLICATE);
}

int main(){
    Mat img = imread("imagen1.jpg");
    Mat mini, maxi, res;
    int tam= 2*10+1; // tamaño de vecindad local
    MinLocal(img, mini, tam, tam);
    MaxLocal(img, maxi, tam, tam);
    res= img-mini;
    maxi= maxi-mini;    
    divide(res, maxi, res, 255.0);   
    imwrite("3-1_Filtro_MaxMin_Estiramiento.jpg", res);
    return 0;
}