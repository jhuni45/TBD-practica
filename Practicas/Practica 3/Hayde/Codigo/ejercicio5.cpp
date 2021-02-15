#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
  Mat img=imread("imagen1.jpg");
  if ( !img.data){
        return -1;
  }
  Mat pt1(1, 3, CV_32FC2); // Puntos en el origen
  pt1.at<Vec2f>(0,0)= Vec2f(0, 0); // Rellenar los tres puntos
  pt1.at<Vec2f>(0,1)= Vec2f(100, 0);
  pt1.at<Vec2f>(0,2)= Vec2f(100, 100);
  Mat pt2(1, 3, CV_32FC2); // Puntos en el destino
  pt2.at<Vec2f>(0,0)= Vec2f(10, 20); // Rellenar los tres puntos
  pt2.at<Vec2f>(0,1)= Vec2f(80, 40);
  pt2.at<Vec2f>(0,2)= Vec2f(20, 70);
  Mat c= getAffineTransform(pt1, pt2);
  warpAffine(img, img, c, img.size());

  imwrite("5_Transformacion_Afin.jpg", img);
  return 0;
}