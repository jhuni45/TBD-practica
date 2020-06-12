#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("imagen1.jpg");
    Mat salida3;
    morphologyEx(img, salida3, MORPH_OPEN, Mat());   
    
    imwrite("4-3_Filtro_Morfologica.jpg", salida3);
    return 0;
}