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
    for (int i= 0; i<10000000; i++) {
        addWeighted(image1, i/100.0, image2, 1-i/100.0, 0, added);
        imshow("Transicion", added);
        waitKey(10);        
    }
}

int ecualization(char * file){
    Mat img= imread(file, 1);
    imshow("Entrada", img);
    Mat gris, hist;
    cvtColor(img, gris, COLOR_BGR2GRAY);
    int canales[1]= {0}, bins[1]= {256};
    float rango[2]= {0, 256};
    const float *rangos[]= {rango};
    calcHist(&gris, 1, canales, noArray(), hist, 1, bins, rangos);
    hist*= 255.0/norm(hist, NORM_L1);
    Mat lut(1, 256, CV_8UC1);
    float acum= 0.0;
    for (int i= 0; i<256; i++) {
        lut.at<uchar>(0, i)= acum;
        acum+= hist.at<float>(i);
    }
    Mat res;
    LUT(img, lut, res);
    imshow("Ecualizada", res);
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
    //gamma(argv[1]);
    //ecualization(argv[1]);
    bi_histogram(argv[1]);
    return 0;
}