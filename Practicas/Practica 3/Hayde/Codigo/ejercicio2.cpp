#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main(){
  Mat img=imread("imagen1.jpg");
	if ( !img.data){
        return -1;
    }
  Mat dst;
  flip (img, dst, 1);
  imwrite("2_Transformacion_Espejo_Horizontal.jpg", dst);
  flip (img, dst, 0);
  imwrite("2_Transformacion_Espejo_Vertical.jpg", dst);
  return 0;
}