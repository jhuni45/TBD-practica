#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

int main(){
  Mat img=imread("imagen1.jpg");
  if ( !img.data){
        return -1;
    }
  resize (img, img, Size(), 2, 2);
  imwrite("1_Transformacion_Zoomx2.jpg", img);
  return 0;
}