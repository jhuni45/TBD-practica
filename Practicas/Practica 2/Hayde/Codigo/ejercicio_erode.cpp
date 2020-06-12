#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("imagen1.jpg");
    Mat salida2;
    erode(img, salida2, Mat()); 
    dilate(salida2, salida2, Mat());
    imwrite("4-1_Filtro_Erode.jpg", salida2);
    return 0;
}