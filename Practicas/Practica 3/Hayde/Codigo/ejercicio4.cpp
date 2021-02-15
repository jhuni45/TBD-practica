#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace cv;
using namespace std;

int main(){
  Mat img=imread("imagen1.jpg");
  if ( !img.data){
        return -1;
    }
  double inc= tan(100*M_PI/180.0);
	Mat c= (Mat_<double>(2, 3) << 1,  inc, -inc*img.size().height/2.0, 0, 1, 0 );
	warpAffine(img, img, c, img.size());
  imwrite("4_Transformacion_Inclinar_100.jpg", img);
  return 0;
}