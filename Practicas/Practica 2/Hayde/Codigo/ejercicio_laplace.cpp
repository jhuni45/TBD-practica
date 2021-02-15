#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    Mat img=imread("imagen1.jpg");
    Mat lap, suma;
    Laplacian(img, lap, CV_16S);
    img.convertTo(img, CV_16S);
    suma = img - 0.4*lap;
    suma.convertTo(img, CV_8U);

    imwrite("1-2_Filtro_Laplace.jpg", img);
    return 0;
}