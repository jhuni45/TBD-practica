#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
    Mat img = imread("imagen1.jpg");
    Mat salida1, salida2;
    Mat kernelPerfilado = (Mat_<float>(3,3) <<-1,-1,-1, -1, 9,-1, -1,-1,-1);
    filter2D(img, salida1, CV_8U, kernelPerfilado);
    imwrite("2-1_Filtro_Mascara_Perfilado.jpg", salida1);
    return 0;
}