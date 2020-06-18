#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("imagen1.jpg");
    Mat salida1, salida2;
    Mat kernelDerivada = (Mat_<float>(3,3) <<-2,-1,0, -1, 0,1, 0,1,2);
    filter2D(img, salida2, CV_8U, kernelDerivada, Point(-1,-1), 128);
    imwrite("2-1_Filtro_Mascara_Derivada.jpg", salida2);
    return 0;
}