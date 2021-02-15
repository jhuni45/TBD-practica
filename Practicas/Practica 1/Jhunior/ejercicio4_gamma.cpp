#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;

int gamma(char * file){
    Mat image1, img32F,aux;
    image1= imread(file,1);
    
    if ( !image1.data ){
        printf("No image data \n");
        return -1;
    }
    image1.convertTo(img32F, CV_32F);
    pow(img32F, 0.5, aux);
    Mat salida;
    aux.convertTo(salida, CV_8U);

    imshow("orginal ", image1);
    imshow("gamma", salida);
    waitKey(0);
}


int main(int argc, char** argv ){
    double alpha_add=0.5;
    if ( argc != 3 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    //uni_histogram(argv[1]);
    //add_images(argv[1],argv[2]);
    gamma(argv[1]);
    //ecualization(argv[1]);
    //bi_histogram(argv[1]);
    return 0;
}