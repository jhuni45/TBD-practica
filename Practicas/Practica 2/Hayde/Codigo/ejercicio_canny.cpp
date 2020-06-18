#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
    
    Mat img=imread("imagen1.jpg");

    Mat gris, bordes;
    cvtColor(img, gris, CV_BGR2GRAY);
    Canny(gris, bordes, 100, 60);

    imwrite("1-3_Filtro_Canny.jpg", bordes);

    return 0;
}