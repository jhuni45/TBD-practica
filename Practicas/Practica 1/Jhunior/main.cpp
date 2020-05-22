#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;

int gray_scale(char * file){
    Mat image;
    image= imread(file,1);
    if ( !image.data ){
        printf("No image data \n");
        return -1;
    }
    Mat gris;
    cvtColor(image,gris,COLOR_BGR2GRAY);
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    imshow("Gray Image",gris);
    waitKey(0);
}

int add_images(char* file1, char *file2){
    Mat image1, image2, added;
    image1= imread(file1,1);
    image2=imread(file2,1);
    if ( !image1.data ){
        printf("No image data \n");
        return -1;
    }
    if ( !image2.data ){
        printf("No image 2 data \n");
        return -1;
    }
    //namedWindow("Display Image", WINDOW_AUTOSIZE );
    for (int i= 0; i<100; i++) {
        addWeighted(image1, i/100.0, image2, 1-i/100.0, 0, added);
        imshow("Transicion", added);
        waitKey(10);        
    }
}

int gamma(char * file){
    
}

int main(int argc, char** argv ){
    double alpha_add=0.5;
    if ( argc != 3 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    //gray_scale(argv[1]);
    add_images(argv[1],argv[2]);
    //gamma(argv[1]);

    
    return 0;
}