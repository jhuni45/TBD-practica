#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;

void MinLocal(Mat entrada, Mat &salida, int ancho, int alto){
	erode(entrada, salida, Mat::ones(alto, ancho, CV_8U),Point(-1,-1), 1, BORDER_REPLICATE);
}

void MaxLocal(Mat entrada, Mat &salida, int ancho, int alto){
	dilate(entrada, salida, Mat::ones(alto, ancho, CV_8U),Point(-1,-1), 1, BORDER_REPLICATE);
}

int get_lineal_arbi(char *file){
	Mat img = imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
    Mat salida1, salida2;
	Mat kernelPerfilado= (Mat_<float>(3, 3) << -1, -1, -1,-1, 9, -1,-1, -1, -1);
	filter2D(img, salida1, CV_8U, kernelPerfilado);
	Mat kernelDerivada= (Mat_<float>(3, 3) << -2, -1, 0,  -1, 0, 1, 0, 1, 2);
	filter2D(img, salida2, CV_8U, kernelDerivada, Point(-1,-1), 128);
	imshow("orginal ", img);
    imshow("canny ", salida2);
    imwrite("salidas/arbitrario.png",salida2);
	waitKey(0);
}

int get_canny (char *file){
	Mat img = imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
	Mat gris, bordes;
	cvtColor(img, gris, COLOR_BGR2GRAY);
	Canny(gris, bordes, 100, 60);

	imshow("orginal ", img);
    imshow("canny ", bordes);
    imwrite("salidas/canny.png",bordes);
	waitKey(0);
}

int get_laplace(char *file){
	Mat img, lap, suma, gray;
	img= imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
	imshow("orginal ", img);
	GaussianBlur( img, img, Size(3, 3), 0, 0, BORDER_DEFAULT );
	cvtColor( img, gray, COLOR_BGR2GRAY );
	//Laplacian(img, lap, CV_16S);
	Laplacian(gray, suma, CV_16S, 3, 1, 0, BORDER_DEFAULT );

	convertScaleAbs( suma, lap );
	//img.convertTo(img, CV_16S);
	//suma= img - 0.4*img;
	//suma.convertTo(img, CV_8U);
	//imshow("lolo ", lap);
	
    imshow("laplace ", lap);
    imwrite("salidas/laplace.png",lap);
	waitKey(0);
}

int get_morpho2(char *file, char *file2){
	Mat img1,img2;
    img1= imread(file,1);
    img2= imread(file2,1);
	if ( !img1.data || !img2.data){
        printf("No image data \n");
        return -1;
    }

	//namedWindow("Transicion", 0);
	Mat int1, int2, res;
	for (float i= 0; i<100; i+=0.1) {
		blur(img1, int1, Size(i*4+1, 1));
		blur(img2, int2, Size((99-i)*4+1, 1));
		addWeighted(int1, 1-i/100.0, int2, i/100.0, 0, res);
		imshow("morfologica 2", res);
    	//imwrite("salidas/morfo2.png",res);
		waitKey(1);
	}
}

int get_morpho(char * file, int ancho){
	Mat img;
    img= imread(file,1);
	if ( !img.data ){
        printf("No image data \n");
        return -1;
    }
	Mat mini, maxi, res;
	int tam= 2*ancho+1;
	// tamaño de vecindad local
	MinLocal(img, mini, tam, tam);
	MaxLocal(img, maxi, tam, tam);
	res= img-mini;maxi= maxi-mini;
	divide(res, maxi, res, 255.0);
	imshow("orginal ", img);
    imshow("morfologica 1", res);
    imwrite("salidas/morfo1.png",res);
	waitKey(0);
}

int get_sobel(char * file){
	Mat img;
    img= imread(file,1);
	if ( !img.data ){
        printf("No image data \n");
        return -1;
    }
	Mat dx, dy, gradiente;
	Sobel(img, dx, CV_32F, 1, 0, -1);
	Sobel(img, dy, CV_32F, 0, 1, -1);
	pow(dx, 2.0, dx);
	pow(dy, 2.0, dy);
	gradiente= dx+dy;
	sqrt(gradiente, gradiente);
	Mat imgrad;
	gradiente.convertTo(imgrad, CV_8U);

	imshow("orginal ", img);
    imshow("sobel", imgrad);
    imwrite("salidas/sobel.png",imgrad);
	waitKey(0);
}


int main(int argc, char** argv ){
    
    if ( argc != 2 ){
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    //get_sobel(argv[1]);
    //get_morpho(argv[1],20);
    //get_morpho2(argv[1],argv[2]);
    //get_laplace(argv[1]);
    //get_canny(argv[1]);
    get_lineal_arbi(argv[1]);
    return 0;
}