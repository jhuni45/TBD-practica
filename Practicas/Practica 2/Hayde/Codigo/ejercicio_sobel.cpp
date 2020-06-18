#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("imagen1.jpg");
    Mat dx, dy, gradiente;
    Sobel(img, dx, CV_32F, 1, 0, -1);
    Sobel(img, dy, CV_32F, 0, 1, -1);
    pow(dx, 2.0, dx);
    pow(dy, 2.0, dy);
    gradiente = dx+dy;
    sqrt(gradiente, gradiente);
    Mat imgrad;
    gradiente.convertTo(imgrad, CV_8U);
    
    imwrite("1-1_Filtro_Sobel.jpg", imgrad);
    return 0;
}