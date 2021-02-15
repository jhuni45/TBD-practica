#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "utils.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <string>

//Matrices de las imagenes
cv::Mat imageMat;
cv::Mat imageMat2;
cv::Mat imageOutputMat;

//Punteros hacia el inicio de la imagen
//Necesarios para luego liberar memoria
uchar4        *d_rgbaImage__;
uchar4        *d_rgba2Image__;
uchar4        *d_outputImage__;

unsigned char *d_binaryImage__;
unsigned char *d_binary2Image__;
unsigned char *d_notImage__;

size_t numRows() { return imageMat.rows; }
size_t numCols() { return imageMat.cols; }

// los tipos de retorno son void ya que cualquier error interno resultará en un cierre
// por eso no se retornan errores...
// Devuelve un puntero de la version RGBA de la imagen de entrada
// y un puntero a la imagend e canal unico de la salida
// para ambos huesped y GPU
void preProcess(uchar4 **inputImage,  uchar4  **outputImage,
                uchar4 **d_rgbaImage, uchar4 **d_outputImage,
                const std::string &filename) {
  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  cv::Mat image;
  image = cv::imread(filename.c_str(), CV_LOAD_IMAGE_COLOR);
  
  if (image.empty()) {
    std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    exit(1);
  }

  cv::cvtColor(image, imageMat, CV_BGR2RGBA);

  // Reserva memoria para el output
  imageOutputMat.create(image.rows, image.cols, CV_8UC4);

  //This shouldn't ever happen given the way the images are created
  //at least based upon my limited understanding of OpenCV, but better to check
  if (!imageMat.isContinuous() || !imageOutputMat.isContinuous()) {
    std::cerr << "Images aren't continuous!! Exiting." << std::endl;
    exit(1);
  }

  //Apuntamos al comienzo de las filas
  *inputImage   = (uchar4 *)imageMat.ptr<unsigned char>(0);
  *outputImage  = (uchar4 *)imageOutputMat.ptr<unsigned char>(0);

  const size_t numPixels = numRows() * numCols();
  //Reserva memoria en el dispositivo
  checkCudaErrors(cudaMalloc(d_rgbaImage,   sizeof(uchar4) * numPixels));
  checkCudaErrors(cudaMalloc(d_outputImage, sizeof(uchar4) * numPixels));
  checkCudaErrors(cudaMemset(*d_outputImage, 0, numPixels * sizeof(uchar4))); // Asegurate de que no queda memoria sin liberar

  // Copia el input en la GPU
  checkCudaErrors(cudaMemcpy(*d_rgbaImage, *inputImage, sizeof(uchar4) * numPixels, cudaMemcpyHostToDevice));

  d_rgbaImage__   = *d_rgbaImage;
  d_outputImage__ = *d_outputImage;
}

//Preprocesar 2 imagenes
void preProcessTwo(uchar4 **inputImage,  uchar4 **inputImage2,  uchar4  **outputImage,
                   uchar4 **d_rgbaImage, uchar4 **d_rgbaImage2, uchar4 **d_outputImage,
                   const std::string &filename, const std::string &filename2) {
  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  cv::Mat image, image2;
  image   = cv::imread(filename.c_str(),  CV_LOAD_IMAGE_COLOR);
  image2  = cv::imread(filename2.c_str(), CV_LOAD_IMAGE_COLOR);
  
  if (image.empty() or image2.empty()) {
    std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    exit(1);
  }

  cv::cvtColor(image,  imageMat,  CV_BGR2RGBA);
  cv::cvtColor(image2, imageMat2, CV_BGR2RGBA);

  // Reserva memoria para el output
  imageOutputMat.create(image.rows, image.cols, CV_8UC4);

  //This shouldn't ever happen given the way the images are created
  //at least based upon my limited understanding of OpenCV, but better to check
  if (!imageMat.isContinuous() || !imageMat2.isContinuous() || !imageOutputMat.isContinuous()) {
    std::cerr << "Images aren't continuous!! Exiting." << std::endl;
    exit(1);
  }

  //Apuntamos al comienzo de las filas
  *inputImage   = (uchar4 *)imageMat.ptr<unsigned char>(0);
  *inputImage2  = (uchar4 *)imageMat2.ptr<unsigned char>(0);
  *outputImage  = (uchar4 *)imageOutputMat.ptr<unsigned char>(0);

  const size_t numPixels = numRows() * numCols();
  //Reserva memoria en el dispositivo
  checkCudaErrors(cudaMalloc(d_rgbaImage,   sizeof(uchar4) * numPixels));
  checkCudaErrors(cudaMalloc(d_rgbaImage2,  sizeof(uchar4) * numPixels));
  checkCudaErrors(cudaMalloc(d_outputImage, sizeof(uchar4) * numPixels));
  checkCudaErrors(cudaMemset(*d_outputImage, 0, numPixels * sizeof(uchar4))); // Asegurate de que no queda memoria sin liberar

  // Copia el input en la GPU
  checkCudaErrors(cudaMemcpy(*d_rgbaImage,  *inputImage, sizeof(uchar4) * numPixels, cudaMemcpyHostToDevice));
  checkCudaErrors(cudaMemcpy(*d_rgbaImage2, *inputImage2, sizeof(uchar4) * numPixels, cudaMemcpyHostToDevice));

  d_rgbaImage__   = *d_rgbaImage;
  d_rgba2Image__  = *d_rgbaImage2;
  d_outputImage__ = *d_outputImage;
}


//Preprocesar una imagen para binarizarla
void preProcessBinary(uchar4 **inputImage,  unsigned char **outputImage,
                      uchar4 **d_inputImage, unsigned char **d_outputImage,
                      const std::string &filename) {
  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  cv::Mat image;
  image = cv::imread(filename.c_str(), CV_LOAD_IMAGE_COLOR);
  
  
  if (image.empty()) {
    std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    exit(1);
  }

  cv::cvtColor(image, imageMat, CV_BGR2RGBA);

  // Reserva memoria para el output
  imageOutputMat.create(image.rows, image.cols, CV_8UC1);

  //This shouldn't ever happen given the way the images are created
  //at least based upon my limited understanding of OpenCV, but better to check
  if (!imageMat.isContinuous() || !imageOutputMat.isContinuous()) {
    std::cerr << "Images aren't continuous!! Exiting." << std::endl;
    exit(1);
  }

  //Apuntamos al comienzo de las filas
  *inputImage   = (uchar4 *)imageMat.ptr<unsigned char>(0);
  *outputImage  = imageOutputMat.ptr<unsigned char>(0);

  const size_t numPixels = numRows() * numCols();
  //Reserva memoria en el dispositivo
  checkCudaErrors(cudaMalloc(d_inputImage,   sizeof(uchar4) * numPixels));
  checkCudaErrors(cudaMalloc(d_outputImage, sizeof(unsigned char) * numPixels));
  checkCudaErrors(cudaMemset(*d_outputImage, 0, numPixels * sizeof(unsigned char))); // Asegurate de que no queda memoria sin liberar

  // Copia el input en la GPU
  checkCudaErrors(cudaMemcpy(*d_inputImage, *inputImage, sizeof(uchar4) * numPixels, cudaMemcpyHostToDevice));

  d_rgbaImage__   = *d_inputImage;
  d_binaryImage__ = *d_outputImage;
}


//Preprocesar una imagen para binarizarla
void preProcessNot(unsigned char **inputImage,  unsigned char **outputImage,
                   unsigned char **d_inputImage, unsigned char **d_outputImage,
                   const std::string &filename) {
  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  cv::Mat image;
  image = cv::imread(filename.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
  imageMat = image;
  
  if (image.empty()) {
    std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    exit(1);
  }


  // Reserva memoria para el output
  imageOutputMat.create(image.rows, image.cols, CV_8UC1);

  //This shouldn't ever happen given the way the images are created
  //at least based upon my limited understanding of OpenCV, but better to check
  if (!imageMat.isContinuous() || !imageOutputMat.isContinuous()) {
    std::cerr << "Images aren't continuous!! Exiting." << std::endl;
    exit(1);
  }

  //Apuntamos al comienzo de las filas
  *inputImage   = image.ptr<unsigned char>(0);
  *outputImage  = imageOutputMat.ptr<unsigned char>(0);

  const size_t numPixels = numRows() * numCols();
  //Reserva memoria en el dispositivo
  checkCudaErrors(cudaMalloc(d_inputImage,   sizeof(unsigned char) * numPixels));
  checkCudaErrors(cudaMalloc(d_outputImage, sizeof(unsigned char) * numPixels));
  checkCudaErrors(cudaMemset(*d_outputImage, 0, numPixels * sizeof(unsigned char))); // Asegurate de que no queda memoria sin liberar

  // Copia el input en la GPU
  checkCudaErrors(cudaMemcpy(*d_inputImage, *inputImage, sizeof(unsigned char) * numPixels, cudaMemcpyHostToDevice));

  d_binaryImage__ = *d_inputImage;
  d_notImage__    = *d_outputImage;
}


//Preprocesar una imagen para binarizarla
void preProcessAnd(unsigned char **inputImage,   unsigned char **inputImage2, unsigned char **outputImage,
                   unsigned char **d_inputImage, unsigned char **d_inputImage2, unsigned char **d_outputImage,
                   const std::string &filename, const std::string &filename2) {
  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  cv::Mat image, image2;
  image = cv::imread(filename.c_str(),  CV_LOAD_IMAGE_GRAYSCALE);
  image2 = cv::imread(filename2.c_str(), CV_LOAD_IMAGE_GRAYSCALE);
  imageMat = image;
  imageMat2 = image2;
  
  if (image.empty() || image2.empty()) {
    std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    exit(1);
  }


  // Reserva memoria para el output
  imageOutputMat.create(image.rows, image.cols, CV_8UC1);

  //This shouldn't ever happen given the way the images are created
  //at least based upon my limited understanding of OpenCV, but better to check
  if (!imageMat.isContinuous() || !imageOutputMat.isContinuous()) {
    std::cerr << "Images aren't continuous!! Exiting." << std::endl;
    exit(1);
  }

  //Apuntamos al comienzo de las filas
  *inputImage   = imageMat.ptr<unsigned char>(0);
  *inputImage2  = imageMat2.ptr<unsigned char>(0);
  *outputImage  = imageOutputMat.ptr<unsigned char>(0);

  const size_t numPixels = numRows() * numCols();
  //Reserva memoria en el dispositivo
  checkCudaErrors(cudaMalloc(d_inputImage,   sizeof(unsigned char) * numPixels));
  checkCudaErrors(cudaMalloc(d_inputImage2,   sizeof(unsigned char) * numPixels));
  checkCudaErrors(cudaMalloc(d_outputImage, sizeof(unsigned char) * numPixels));
  checkCudaErrors(cudaMemset(*d_outputImage, 0, numPixels * sizeof(unsigned char))); // Asegurate de que no queda memoria sin liberar

  // Copia el input en la GPU
  checkCudaErrors(cudaMemcpy(*d_inputImage,  *inputImage, sizeof(unsigned char) * numPixels, cudaMemcpyHostToDevice));
  checkCudaErrors(cudaMemcpy(*d_inputImage2, *inputImage2, sizeof(unsigned char) * numPixels, cudaMemcpyHostToDevice));

  d_binaryImage__   = *d_inputImage;
  d_binary2Image__  = *d_inputImage2;
  d_notImage__      = *d_outputImage;
}