// main.cpp

#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


////////////////////////////////////////////////////////////////////////
//Realizar el zoom 2x de una imagen img (modo in-place)
void get_zoom_2x(std::string filename){
	cv::Mat image = cv::imread(filename,1);
	if ( !image.data){
        printf("No image data \n");
    }
	cv::imshow("Original", image);
	cv::resize (image, image, cv::Size(), 2, 2);

    cv::imshow("Zoom 2x", image);
    //cv::imwrite("Output/zoom.png",image);
	cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
//Realizar el espejo vertical y horizontal de una imagen
void get_flip(std::string filename, int flipCode){
	cv::Mat image = cv::imread(filename,1);
	if ( !image.data){
        printf("No image data \n");
        return;
    }
    cv::Mat destination;
	cv::imshow("Original ", image);
	cv::flip(image, destination, flipCode);
    cv::imshow("Flip", destination);
    //cv::imwrite("Output/flip.png",image);
	cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
//Rotar y escalar una imagen indicando ángulo y escala
void Rotate(cv::Mat imagen, cv::Mat &salida, double angulo, double escala = 1){
	double w= imagen.size().width, h= imagen.size().height;
	double sa= sin(angulo*M_PI/180), ca= cos(angulo*M_PI/180);
	double cx= -w/2*ca-h/2*sa, cy= w/2*sa-h/2*ca;
	sa= fabs(sa);
	ca= fabs(ca);
	cv::Size tam((w*ca+h*sa)*escala, (h*ca+w*sa)*escala);
	cv::Mat M= cv::getRotationMatrix2D(cv::Point2f(0,0), angulo, escala);
	M.at<double>(0,2)= tam.width/2+cx*escala;
	M.at<double>(1,2)= tam.height/2+cy*escala;
	cv::warpAffine(imagen, salida, M, tam);
}

void get_rotate(std::string filename, float angle){
	cv::Mat image = cv::imread(filename,1);
	if ( !image.data){
        printf("No image data \n");
        return;
    }
    cv::Mat out;
    cv::imshow("Original", image);
    Rotate(image, out, angle);
    cv::imshow("Rotation", out);
	cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
//Inclinar (shear) la imagen img en X en angulo grados y desplazar en X 
//para que se quede centrada.
void get_shear(std::string filename, float angle){
	cv::Mat image = cv::imread(filename,1);
	if ( !image.data){
        printf("No image data \n");
        return;
    }
    cv::imshow("Original", image);
	double inc = tan(angle*M_PI/180.0);
	cv::Mat c  = (cv::Mat_<double>(2, 3) << 1,  inc,  -inc*image.size().height/2.0, 0,  1,   0 );
	cv::warpAffine(image, image, c, image.size());
	cv::imshow("Shear", image);
	cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
//Aplicar una transformación afín a una imagen img, suponiendo que
//tenemos 3 puntos en img y los 3 puntos correspondientes en destino
void get_affine(std::string filename){
	cv::Mat img = cv::imread(filename,1);
	if ( !img.data){
        printf("No image data \n");
        return;
    }
    cv::imshow("Original", img);
	cv::Mat pt1(1, 3, CV_32FC2);
	pt1.at<cv::Vec2f>(0,0) = cv::Vec2f(0, 0);
	pt1.at<cv::Vec2f>(0,1) = cv::Vec2f(100, 0);
	pt1.at<cv::Vec2f>(0,2) = cv::Vec2f(100, 100);
	cv::Mat pt2(1, 3, CV_32FC2);
	pt2.at<cv::Vec2f>(0,0) = cv::Vec2f(10, 20);
	pt2.at<cv::Vec2f>(0,1) = cv::Vec2f(80, 40);
	pt2.at<cv::Vec2f>(0,2) = cv::Vec2f(20, 70);
	cv::Mat c = cv::getAffineTransform(pt1, pt2);
	cv::warpAffine(img, img, c, img.size());
	cv::imshow("Affine Transform", img);
	cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {

    std::string exercise;
    std::string filename;

    int   aux;
    float auxf;

    exercise = std::string( argv[1] );

    switch (argc)
    {
    case 3:

        //Invocar zoom2x
        if( exercise == "-z" ){
            filename = std::string( argv[2] );
            get_zoom_2x( filename );
        }
        //Invocar affine
        else if( exercise == "-a" ){
            filename = std::string( argv[2] );
            get_affine( filename );
        }
        else{
            printf("Incorrect command\n");
        }


        break;
    
    case 4:

        //Invocar flip
        if( exercise == "-f" ){
            filename = std::string( argv[2] );
            aux      = std::stoi( argv[3] );

            get_flip(filename, aux);
        }
        //Invocar rotation
        else if( exercise == "-r" ){
            filename = std::string( argv[2] );
            auxf     = std::stof( argv[3] );

            get_rotate(filename, auxf);
        }
        //Invocar shear
        else if( exercise == "-s" ){
            filename = std::string( argv[2] );
            auxf     = std::stof( argv[3] );

            get_shear(filename, auxf);
        }
        else{
            printf("Incorrect command\n");
        }

        break;

    default:
        printf("Incorrect command\n");
        printf("Parameters: [-z | -a] [image] \n");
        printf("Parameters: [-f | -r] [image] [aux_number] \n");
        break;
    }

    return 0;
}
