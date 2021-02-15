#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;

int uni_histogram(char * file){
    Mat image,gris,hist;
    image= imread(file,1);
    if ( !image.data ){
        printf("No image data \n");
        return -1;
    }
    cvtColor(image,gris,COLOR_BGR2GRAY);
    
    int canales[1]= {0};
    int bins[1]= {256};
    float rango[2]= {0, 256};
    const float *rangos[]= {rango};
    calcHist(&gris, 1, canales, noArray(), hist, 1, bins, rangos);
    for (int i= 0; i<256; i++)
        printf("Celda %d: %g", i, hist.at<float>(i));

    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    imshow("Gray Image",gris);
    waitKey(0);
}

int main(int argc, char** argv ){
    double alpha_add=0.5;
    if ( argc != 3 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    uni_histogram(argv[1]);
    return 0;
}