// main.cpp

#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Filtro Sobel
void get_sobel( std::string filename ){
    
    cv::Mat image;
    image = cv::imread(filename, 1);
    if( image.empty() ){
        printf("No se pudo cargar la imagen\n");
        return;
    }

    cv::Mat dx, dy, gradient;
    cv::Sobel(image, dx, CV_32F, 1, 0, -1);
    cv::Sobel(image, dy, CV_32F, 0, 1, -1);
    pow(dx, 2.0, dx);
    pow(dy, 2.0, dy);
    gradient = dx + dy;
    sqrt(gradient, gradient);
    cv::Mat imgrad; 
    gradient.convertTo(imgrad, CV_8U);

    //Guardamos la imagen
    cv::imwrite("Output/sobel.png", imgrad  );

    //Mostramos la imagen
    cv::imshow(" Entrada " , image );
    cv::imshow(" Sobel "   , imgrad);
    cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Filtro de Laplace
void get_laplace( std::string filename ){
    cv::Mat image, lap, suma;

    image = cv::imread(filename, 1);
    if( image.empty() ){
        printf("No se pudo cargar la imagen\n");
        return;
    }
    cv::imshow(" Entrada " , image );

    cv::Laplacian(image, lap, CV_16S);
    image.convertTo(image, CV_16S);
    suma = image - 0.4*lap; 
    suma.convertTo(image, CV_8U);

    //Guardamos la imagen
    cv::imwrite("Output/laplace.png", image );

    //Mostramos la imagen
    cv::imshow(" Laplacian "   , image );
    cv::waitKey(0);

}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Filtro de borde de Canny
void get_canny( std::string filename ){

    cv::Mat image;
    image = cv::imread(filename, 1);
    if( image.empty() ){
        printf("No se pudo cargar la imagen\n");
        return;
    }

    cv::Mat gray, borders;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY); 
    cv::Canny(gray, borders, 100, 60);
    
    //Guardamos la imagen
    cv::imwrite("Output/canny.png", borders  );

    //Mostramos la imagen
    cv::imshow(" Entrada " , image  );
    cv::imshow(" Canny "   , borders);
    cv::waitKey(0);
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Filtro de máscara de convolución arbitraria
void get_arbitrary( std::string filename ){

    cv::Mat image;
    image = cv::imread(filename, 1);
    if( image.empty() ){
        printf("No se pudo cargar la imagen\n");
        return;
    }

    cv::Mat output1, output2;
    cv::Mat kernelPerfilado = (cv::Mat_<float>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1); 
    cv::filter2D(image, output1, CV_8U, kernelPerfilado);
    cv::Mat kernelDerivada = (cv::Mat_<float>(3, 3) << -2, -1, 0, -1, 0, 1, 0, 1, 2); 
    cv::filter2D(image, output2, CV_8U, kernelDerivada, cv::Point(-1,-1), 128);

    //Guardamos la imagen
    cv::imwrite("Output/arbitrary.png", output2  );

    //Mostramos la imagen
    cv::imshow(" Entrada "   , image  );
    cv::imshow(" Arbitrary " , output2);
    cv::waitKey(0);

}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
void MinLocal (cv::Mat input, cv::Mat &output, int width, int height){

    cv::erode(input, output, cv::Mat::ones(height, width, CV_8U),
              cv::Point(-1,-1), 1, cv::BORDER_REPLICATE); 
}

void MaxLocal (cv::Mat input, cv::Mat &output, int width, int height){
    cv::dilate(input, output, cv::Mat::ones(height, width, CV_8U),
               cv::Point(-1,-1), 1, cv::BORDER_REPLICATE); 
}

//Filtro de ajuste local del histograma
void get_localAdjust( std::string filename, int width ){
    
    cv::Mat image;
    image = cv::imread(filename, 1);
    if( image.empty() ){
        printf("No se pudo cargar la imagen\n");
        return;
    }

    cv::Mat mini, maxi, result;
    
    int tam = 2 * width + 1; // tamaño de vecindad local 
    MinLocal(image, mini, tam, tam);
    MaxLocal(image, maxi, tam, tam);
 
    result = image  - mini;
    maxi   = maxi   - mini;
    
    cv::divide(result, maxi, result, 255.0);

    //Guardamos la imagen
    cv::imwrite("Output/localAdjust.png", result  );

    //Mostramos la imagen
    cv::imshow(" Entrada "      , image );
    cv::imshow(" Local Adjustment " , result);
    cv::waitKey(0);


}
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Filtro de suavizado intermedio
void get_smoothing( std::string filename1, std::string filename2 ){

    cv::Mat image1, image2;
    image1 = cv::imread(filename1, 1);
    image2 = cv::imread(filename2, 1);

    if( image1.empty() || image2.empty() ){
        printf("No se pudo cargar la imagen\n");
        return;
    }

    cv::Mat int1, int2, result;
    for (int i= 0; i<100; i++) {
    cv::blur(image1, int1, cv::Size(i*4+1, 1)     );
    cv::blur(image2, int2, cv::Size((99-i)*4+1, 1)); 
    cv::addWeighted(int1, 1-i/100.0, int2, i/100.0, 0, result); 
    cv::imshow( "Transicion", result );
    cv::waitKey(1);
    }



}



////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {

    std::string exercise;
    std::string filename;
    std::string filename2;
    int         width;

    if(  !(argc == 3 || argc == 4) ){
        std::cout << "./pract2 [ejecicio] [imagen] " << std::endl;
        return -1;
    }

    else {
        
        exercise = std::string( argv[1] );

        //Llamada ejercicio "Sobel"
        if( exercise == "-s" ){
            filename = std::string( argv[2] );
            get_sobel(filename);
        }

        //Llamada ejercicio "Laplace"
        if( exercise == "-l" ){
            filename = std::string( argv[2] );
            get_laplace(filename);
        }

        //Llamada ejercicio "Canny"
        if( exercise == "-c" ){
            filename = std::string( argv[2] );
            get_canny(filename);
        }

        //Llamada ejercicio "Arbitrary"
        if( exercise == "-a" ){
            filename = std::string( argv[2] );
            get_arbitrary(filename);
        }

        //Llamada ejercicio "Local Adjustment"
        if( exercise == "-m1" && argc == 4 ){
            filename = std::string( argv[2] );
            width    = std::atoi( argv[3] );
            get_localAdjust(filename, width);
        }

        //Llamada ejercicio "Smoothing"
        if( exercise == "-m2" && argc == 4 ){
            filename = std::string( argv[2] );
            filename2 = std::string( argv[3] );
            get_smoothing(filename, filename2);
        }

    }


    return 0;
}
