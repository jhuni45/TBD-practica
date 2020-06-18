#include <stdio.h>
#include <opencv2/opencv.hpp>


using namespace cv;


int get_zoom2x(char * file){
	Mat img = imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
	imshow("orginal ", img);
	resize (img, img, Size(), 2, 1);

    imshow("zoom2x", img);
    imwrite("salidas/zoom2x.png",img);
	waitKey(0);
}

int get_flip(char * file, int flipCode){
	Mat img = imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
    Mat dst;
	imshow("orginal ", img);
	flip(img, dst, flipCode);
    imshow("flip", dst);
    imwrite("salidas/flip.png",dst);
	waitKey(0);
}


void Rotar(Mat imagen, Mat &salida, double angulo, double escala= 1){
	double w= imagen.size().width, h= imagen.size().height;
	double sa= sin(angulo*M_PI/180), ca= cos(angulo*M_PI/180);
	double cx= -w/2*ca-h/2*sa, cy= w/2*sa-h/2*ca;
	sa= fabs(sa);
	ca= fabs(ca);
	Size tam((w*ca+h*sa)*escala, (h*ca+w*sa)*escala);
	Mat M= getRotationMatrix2D(Point2f(0,0), angulo, escala);
	M.at<double>(0,2)= tam.width/2+cx*escala;
	M.at<double>(1,2)= tam.height/2+cy*escala;
	warpAffine(imagen, salida, M, tam);
}

int get_rotar(char * file, float angulo){
	Mat img = imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
    Mat out;
    imshow("original", img);
    Rotar(img,out, angulo);
    imshow("rotacion", out);
    imwrite("salidas/rotar.png",out);
	waitKey(0);
}

int get_shear(char *file, float value){
	Mat img = imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
    imshow("original", img);
	double inc= tan(value*M_PI/180.0);
	Mat c= (Mat_<double>(2, 3) << 1,  inc,  -inc*img.size().height/2.0, 0,  1,   0 );
	warpAffine(img, img, c, img.size());
	imshow("inclinacion", img);
    imwrite("salidas/inclinacion.png",img);
	waitKey(0);
}


int get_affine(char * file){
	Mat img = imread(file,1);
	if ( !img.data){
        printf("No image data \n");
        return -1;
    }
    imshow("original", img);
	Mat pt1(1, 3, CV_32FC2);
	pt1.at<Vec2f>(0,0)= Vec2f(0, 0);
	pt1.at<Vec2f>(0,1)= Vec2f(100, 0);
	pt1.at<Vec2f>(0,2)= Vec2f(100, 100);
	Mat pt2(1, 3, CV_32FC2);
	pt2.at<Vec2f>(0,0)= Vec2f(10, 20);
	pt2.at<Vec2f>(0,1)= Vec2f(80, 40);
	pt2.at<Vec2f>(0,2)= Vec2f(20, 70);
	Mat c= getAffineTransform(pt1, pt2);
	warpAffine(img, img, c, img.size());
	imshow("affine_transform", img);
    imwrite("salidas/affine.png",img);
	waitKey(0);
}

int main(int argc, char** argv ){
	if (strcmp(argv[1], "-z")== 0) {
		if ( argc != 3 ){
        	printf("Parametros: <funcion> <imagen>\nEjemplo: -z image.png\n");
        return -1;
    	}
	    get_zoom2x(argv[2]);
	}
	else if (strcmp(argv[1], "-f")== 0){
		if ( argc != 4 ){
        	printf("Parametros: <funcion> <imagen> <int (puede ser  0, 1, -1)> \nEjemplo: -f image.png 1\n");
        return -1;
    	}
	    int flipcode = strtol(argv[3], NULL, 10);
    	get_flip(argv[2], flipcode);

	}
	else if (strcmp(argv[1], "-r")== 0){
		if ( argc != 4 ){
        	printf("Parametros: <funcion> <imagen> <float> \nEjemplo: -r image.png 10\n");
        return -1;
    	}
		float angulo = atof(argv[3]);
    	get_rotar(argv[2],angulo);
	}
	else if (strcmp(argv[1], "-s")== 0){
		if ( argc != 4 ){
        	printf("Parametros: <funcion> <imagen> <float> \nEjemplo: -s image.png 10\n");
        return -1;
    	}
		float value = atof(argv[3]);
		get_shear(argv[2], value);		
	}
	else if (strcmp(argv[1], "-a")== 0){
		if ( argc != 3 ){
        	printf("Parametros: <funcion> <imagen> \nEjemplo: -a image.png\n");
        return -1;
    	}
	    get_affine(argv[2]);
	}
	else
		printf("comandos invalidos\n");

    return 0;
}