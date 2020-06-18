#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
void rezise(char* file){
    Mat input_image1;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }
    resize (input_image1, input_image1, Size(), 2, 2);
    imwrite( "rezise.jpg", input_image1 );
}
void flip(char* file){
    Mat input_image1,dst;
    input_image1 = imread( file, 1 );

    if( !input_image1.data )
    {
        cout<< " No image data \n ";
        return;
    }

    flip (input_image1, dst, 0);
    imwrite( "flip.jpg", dst );
}
void rotar (char* file){
    double angulo = 45;
    double escala=1;
    Mat imagen,salida;
    imagen = imread( file, 1 );

    if( !imagen.data )
    {
        cout<< " No image data \n ";
        return;
    }

    double w= imagen.size().width, h= imagen.size().height;
    double sa= sin(angulo*M_PI/180), ca= cos(angulo*M_PI/180);
    double cx= -w/2*ca-h/2*sa, cy= w/2*sa-h/2*ca;
    sa= fabs(sa); ca= fabs(ca);
    Size tam((w*ca+h*sa)*escala, (h*ca+w*sa)*escala);
    Mat M= getRotationMatrix2D(Point2f(0,0), angulo, escala);
    M.at<double>(0,2)= tam.width/2+cx*escala;
    M.at<double>(1,2)= tam.height/2+cy*escala;
    warpAffine(imagen, salida, M, tam);
    imwrite( "rotar.jpg", salida );
}

void inclinar(char* file){
    Mat img;
    img = imread( file, 1 );

    if( !img.data )
    {
        cout<< " No image data \n ";
        return;
    }

    double inc= tan(180.0*M_PI/180.0);
    Mat c= (Mat_<double>(2, 3) << 1, inc, -inc*img.size().height/2.0, 0, 1, 0 );
    warpAffine(img, img, c, img.size());
    imwrite( "inclinar.jpg", img );
}
void transformacion_afin(char* file){
    Mat img;
    img = imread( file, 1 );

    if( !img.data )
    {
        cout<< " No image data \n ";
        return;
    }

    Mat pt1(1, 3, CV_32FC2); // Puntos en el origen
    pt1.at<Vec2f>(0,0)= Vec2f(0, 0); // Rellenar los tres puntos
    pt1.at<Vec2f>(0,1)= Vec2f(100, 0);
    pt1.at<Vec2f>(0,2)= Vec2f(100, 100);
    Mat pt2(1, 3, CV_32FC2); // Puntos en el destino
    pt2.at<Vec2f>(0,0)= Vec2f(10, 20); // Rellenar los tres puntos
    pt2.at<Vec2f>(0,1)= Vec2f(80, 40);
    pt2.at<Vec2f>(0,2)= Vec2f(20, 70);
    Mat c= getAffineTransform(pt1, pt2);
    warpAffine(img, img, c, img.size());
    imwrite( "transformacion_afin.jpg", img );
}

int main(int argc, char **argv)
{
    rezise(argv[1]);
    flip(argv[2]);
    rotar(argv[1]);
    inclinar(argv[2]);
    transformacion_afin(argv[1]);
    return 0;
}