#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

void Rotate(Mat imagen, Mat &salida, double angulo, double escala = 1){
	double w= imagen.size().width, h= imagen.size().height;
	double sa= sin(angulo*M_PI/180), ca= cos(angulo*M_PI/180);
	double cx= -w/2*ca-h/2*sa, cy= w/2*sa-h/2*ca;
	sa= fabs(sa);
	ca= fabs(ca);
	Size tam((w*ca+h*sa)*escala, (h*ca+w*sa)*escala);
	Mat M= getRotationMatrix2D(Point2f(0,0), angulo, escala);
	M.at<double>(0,2)= tam.width/2+cx*escala;
	M.at<double>(1,2)= tam.height/2+cy*escala;
	warpAffine(imagen, salida, M, tam);
}

int main(){
	Mat image = imread("imagen1.jpg");
	if ( !image.data){
        return -1;
    }
    Mat destination;
    Rotate(image, destination, 25);
    imwrite("3_Transformacion_RotarEscalar_25.jpg", destination);
    Rotate(image, destination, 50);
    imwrite("3_Transformacion_RotarEscalar_50.jpg", destination);
    Rotate(image, destination, 75);
    imwrite("3_Transformacion_RotarEscalar_75.jpg", destination);
    Rotate(image, destination, 100);
    imwrite("3_Transformacion_RotarEscalar_100.jpg", destination);
    Rotate(image, destination, 125);
    imwrite("3_Transformacion_RotarEscalar_125.jpg", destination);
    Rotate(image, destination, 150);
    imwrite("3_Transformacion_RotarEscalar_150.jpg", destination);
  return 0;
}