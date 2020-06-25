// main.cpp

#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


////////////////////////////////////////////////////////////////////////
//Transformación perspectiva de una imagen, img, para producir un efecto similar al de la figura
void transform_perspective(std::string filename){
	cv::Mat image = cv::imread(filename,1);
	if ( !image.data){
        printf("No image data \n");
    }
	cv::imshow("Original", image);

    double w= image.size().width, h= image.size().height;
    cv::Mat pt1(1, 4, CV_32FC2); // Cuatro puntos en el origen
    pt1.at<cv::Vec2f>(0,0)= cv::Vec2f(0, 0);
    pt1.at<cv::Vec2f>(0,1)= cv::Vec2f(w, 0);
    pt1.at<cv::Vec2f>(0,2)= cv::Vec2f(w, h);
    pt1.at<cv::Vec2f>(0,3)= cv::Vec2f(0, h);
    cv::Mat pt2(1, 4, CV_32FC2); // Cuatro puntos en el destino
    pt2.at<cv::Vec2f>(0,0)= cv::Vec2f(w*0.3, 0);
    pt2.at<cv::Vec2f>(0,1)= cv::Vec2f(w*0.7, 0);
    pt2.at<cv::Vec2f>(0,2)= cv::Vec2f(w, h);
    pt2.at<cv::Vec2f>(0,3)= cv::Vec2f(0, h);
    cv::Mat c = cv::getPerspectiveTransform(pt1, pt2);
    cv::Mat result;
    warpPerspective(image, result, c, image.size());

    cv::imshow("Perspective", result);
    cv::imwrite("Output/perspective.png",result);
	cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
//Transformación aleatoria de una imagen img, con un radio de deformación de m
void remap_image(std::string filename, int m){
	cv::Mat image = cv::imread(filename,1);
	if ( !image.data){
        printf("No image data \n");
        return;
    }
	cv::imshow("Original", image);

    cv::Mat mapa1(image.size(), CV_32FC1);
    cv::Mat mapa2(image.size(), CV_32FC1);
    for (int y= 0; y<image.size().height; y++)
    for (int x= 0; x<image.size().width; x++) {
    mapa1.at<float>(y, x)= x+rand()%(2*m+1) - m; // Mapa 1
    mapa2.at<float>(y, x)= y+rand()%(2*m+1) - m; // Mapa 2
    }
    cv::Mat result;
    remap(image, result, mapa1, mapa2, cv::INTER_NEAREST);

    cv::imshow("Remap " + std::to_string(m), result);
    cv::imwrite("Output/remap_" + std::to_string(m) + ".png",result);
	cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
//Transformación de acristalado. En el código anterior, sustituir las líneas comentadas por
void transform_acristalado(std::string filename, int m){
	cv::Mat image = cv::imread(filename,1);
	if ( !image.data){
        printf("No image data \n");
        return;
    }
	cv::imshow("Original", image);

    cv::Mat mapa1(image.size(), CV_32FC1);
    cv::Mat mapa2(image.size(), CV_32FC1);
    for (int y= 0; y<image.size().height; y++)
    for (int x= 0; x<image.size().width; x++) {
    mapa1.at<float>(y, x)= x - x%m + y%m; // Mapa 1 cambiado
    mapa2.at<float>(y, x)= y - y%m + x%m; // Mapa 2 cambiado
    }
    cv::Mat result;
    remap(image, result, mapa1, mapa2, cv::INTER_NEAREST);

    cv::imshow("Acristalado" + std::to_string(m), result);
    cv::imwrite("Output/acristalado_" + std::to_string(m) + ".png",result);
	cv::waitKey(0);
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {

    std::string exercise;
    std::string filename;

    int   aux;

    exercise = std::string( argv[1] );

    switch (argc)
    {
    case 3:

        //Invocar perspective
        if( exercise == "-p" ){
            filename = std::string( argv[2] );
            transform_perspective( filename );
        }
        else{
            printf("Incorrect command\n");
        }


        break;
    
    case 4:

        //Invocar remap
        if( exercise == "-r" ){
            filename = std::string( argv[2] );
            aux      = std::stoi( argv[3] );

            remap_image(filename, aux);
        }
        //Invocar acristalada
        else if( exercise == "-a" ){
            filename = std::string( argv[2] );
            aux      = std::stoi( argv[3] );

            transform_acristalado(filename, aux);
        }
        else{
            printf("Incorrect command\n");
        }

        break;

    default:
        printf("Incorrect command\n");
        printf("Parameters: [-p] [image] \n");
        printf("Parameters: [ -r | -a] [image] [aux_number] \n");
        break;
    }

    return 0;
}
