#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;

int bi_histogram(char * file){
    Mat img= imread(file, 1);
    imshow("Entrada", img);
    Mat hist;
    int canales[2]= {2, 1};
    int bins[2]= {64, 64};
    float rango[2]= {0, 256};
    const float *rangos[]= {rango, rango};
    calcHist(&img, 1, canales, noArray(), hist, 2, bins, rangos);
    Mat pinta(64, 64, CV_8UC1);
    double minval, maxval;
    minMaxLoc(hist, &minval, &maxval);
    for (int r= 0; r<64; r++)
        for (int g= 0; g<64; g++)
            pinta.at<uchar>(r, g)= 255-255*hist.at<float>(r, g)/maxval;
    namedWindow("Histograma R-G", 0);
    imshow("Histograma R-G", pinta);
    waitKey(0);
}



int main(int argc, char** argv ){
    double alpha_add=0.5;
    if ( argc != 3 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    bi_histogram(argv[1]);
    return 0;
}