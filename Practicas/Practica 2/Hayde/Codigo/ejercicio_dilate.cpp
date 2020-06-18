#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("imagen1.jpg");
    Mat salida1;
    dilate(img, salida1, Mat::eye(5,5,CV_8U));
  
    imwrite("4-2_Filtro_Dilate.jpg", salida1);
    return 0;
}