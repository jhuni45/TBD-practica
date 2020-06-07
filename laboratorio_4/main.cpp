#include <iostream>
#include "utils.h"
#include <string>
#include <stdio.h>

// Declaramos la funcion que invoca al kernel
void gamma_correction(uchar4* const d_rgbaImage,
                      uchar4* const d_greyImage, 
                      size_t numRows, size_t numCols, float gamma);

void image_addition(uchar4* const d_rgbaImage, 
                    uchar4* const d_rgbaImage2,
                    uchar4* const d_outputImage, 
                    size_t numRows, size_t numCols, float percent);

void image_binarization(uchar4* const d_rgbaImage, 
                        unsigned char* const d_outputImage, 
                        size_t numRows, size_t numCols, int threshold);

void operator_not_image(unsigned char* const d_inputImage, 
                        unsigned char* const d_outputImage, 
                        size_t numRows, size_t numCols);

void operator_and_image(unsigned char* const d_inputImage, 
                        unsigned char* const d_inputImage2, 
                        unsigned char* const d_outputImage, 
                        size_t numRows, size_t numCols);

void operator_or_image(unsigned char* const d_inputImage, 
                       unsigned char* const d_inputImage2, 
                       unsigned char* const d_outputImage, 
                       size_t numRows, size_t numCols);                        


// Incluye las definiciones de las funciones de arriba
#include "preprocess.cpp"

int main(int argc, char **argv) {
  uchar4        *h_rgbaImage,   *d_rgbaImage;
  uchar4        *h_rgbaImage2,  *d_rgbaImage2;
  uchar4        *h_outputImage, *d_outputImage;

  //Variable para binarizar
  unsigned char *h_binaryImage,  *d_binaryImage;   //imagen binarizada
  unsigned char *h_binary2Image, *d_binary2Image;  //imagen binarizada
  unsigned char *h_notImage,     *d_notImage;      //imagen negada

  //Datos auxiliares
  std::string input_file;
  std::string input_file2;
  std::string output_file;
  float aux;
  std::string exercise = std::string(argv[1]);

  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  switch (argc)
  { 
    case 3:

      //Caso ecualización de imagen
      if( exercise == "-eq" ){

      }

      //Caso negación de imagen
      //De preferencia una imagen binaria
      if( exercise == "-not" ){

          input_file  = std::string(argv[2]);
          output_file = input_file + "_not.png";

          preProcessNot(&h_binaryImage, &h_notImage,
                        &d_binaryImage, &d_notImage,
                        input_file);

          operator_not_image(d_binaryImage, d_notImage, numRows(), numCols());

          size_t numPixels = numRows()*numCols();
          checkCudaErrors(cudaMemcpy(h_notImage, d_notImage, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost));

          cv::Mat output(numRows(), numCols(), CV_8UC1, (void*)h_notImage);

          cv::imwrite(output_file.c_str(), output);

          /* Libera memoria */
          cudaFree(d_binaryImage__);
          cudaFree(d_notImage__);

      }

      break;


    case 4:
      
      //Caso gamma "-g" , gamma = aux
      if( exercise == "-g"  ){

          input_file   = std::string(argv[2]);
          output_file  = input_file + "_gamma.png";
          aux          = atof(argv[3]); //gamma

          // Carga la imagen y nos prepara los punteros para la entrada y  
          // salida de datos
          preProcess(&h_rgbaImage, &h_outputImage, 
                     &d_rgbaImage, &d_outputImage, input_file);

          // Invoca al código de kernel para ser llamado.
          gamma_correction(d_rgbaImage, d_outputImage, numRows(), numCols(), aux);

          size_t numPixels = numRows()*numCols();
          checkCudaErrors(cudaMemcpy(h_outputImage, d_outputImage, sizeof(uchar4) * numPixels, cudaMemcpyDeviceToHost));

          /* Saca la imagen en escala de grises */
          cv::Mat output(numRows(), numCols(), CV_8UC4, (void*)h_outputImage);
          // std::cout << "M = " << std::endl << " "  << output << std::endl << std::endl;
          // Para imprimir la imagen en una ventana
          // // Abre la ventana
          // cv::namedWindow("to_bw");
          //  // Pasa la imagen a la ventana anterior
          // cv::imshow("to_bw", output);
          // cvWaitKey (0);
          // cvDestroyWindow ("to_bw");
          // Guardar a fichero
          cv::imwrite(output_file.c_str(), output);

          /* Libera memoria */
          cudaFree(d_rgbaImage__);
          cudaFree(d_outputImage__);


      }

      if( exercise == "-b" ){

          input_file  = std::string(argv[2]);
          output_file = input_file + "_binary.png";
          aux         = atof(argv[3]); //threshold básico

          //preprocesamos la imagen para convertira a binario
          preProcessBinary(&h_rgbaImage, &h_binaryImage, 
                           &d_rgbaImage, &d_binaryImage, input_file);

          image_binarization(d_rgbaImage, d_binaryImage, numRows(), numCols(), (int) aux );
          size_t numPixels = numRows()*numCols();
          checkCudaErrors(cudaMemcpy(h_binaryImage, d_binaryImage, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost));

          cv::Mat output(numRows(), numCols(), CV_8UC1, (void*)h_binaryImage);
          cv::imwrite(output_file.c_str(), output);

          /* Libera memoria */
          cudaFree(d_rgbaImage__);
          cudaFree(d_binaryImage__);


      }

      //Caso operador AND entre 2 imágenes
      if( exercise == "-and" ){
          input_file  = std::string(argv[2]);
          input_file2 = std::string(argv[3]);
          output_file = input_file + "_and.png";

          preProcessAnd(&h_binaryImage, &h_binary2Image, &h_notImage,
                        &d_binaryImage, &d_binary2Image, &d_notImage,
                        input_file, input_file2);

          operator_and_image(d_binaryImage, d_binary2Image, d_notImage, numRows(), numCols());

          size_t numPixels = numRows()*numCols();
          checkCudaErrors(cudaMemcpy(h_notImage, d_notImage, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost));

          cv::Mat output(numRows(), numCols(), CV_8UC1, (void*)h_notImage);

          cv::imwrite(output_file.c_str(), output);


          cudaFree(d_binaryImage__);
          cudaFree(d_binary2Image__);
          cudaFree(d_notImage__);

      }

      //Caso operador OR entre 2 imágenes
      if( exercise == "-or" ){
          input_file  = std::string(argv[2]);
          input_file2 = std::string(argv[3]);
          output_file = input_file + "_or.png";

          preProcessAnd(&h_binaryImage, &h_binary2Image, &h_notImage,
                        &d_binaryImage, &d_binary2Image, &d_notImage,
                        input_file, input_file2);

          operator_or_image(d_binaryImage, d_binary2Image, d_notImage, numRows(), numCols());

          size_t numPixels = numRows()*numCols();
          checkCudaErrors(cudaMemcpy(h_notImage, d_notImage, sizeof(unsigned char) * numPixels, cudaMemcpyDeviceToHost));

          cv::Mat output(numRows(), numCols(), CV_8UC1, (void*)h_notImage);

          cv::imwrite(output_file.c_str(), output);


          cudaFree(d_binaryImage__);
          cudaFree(d_binary2Image__);
          cudaFree(d_notImage__);
      }

      
      break;

    case 5:
      //Caso suma de 2 imágenes (media ponderada)
      if( exercise == "-s" ){

          input_file  = std::string(argv[2]);
          input_file2 = std::string(argv[3]);
          aux         = atof(argv[4]); //porcentaje suma
          output_file = input_file + "_suma.png";

          preProcessTwo(&h_rgbaImage, &h_rgbaImage2, &h_outputImage,
                     &d_rgbaImage, &d_rgbaImage2, &d_outputImage, 
                     input_file, input_file2);

          
          image_addition(d_rgbaImage, d_rgbaImage2, d_outputImage, 
                         numRows(), numCols(), aux);

          size_t numPixels = numRows()*numCols();
          checkCudaErrors(cudaMemcpy(h_outputImage, d_outputImage, sizeof(uchar4) * numPixels, cudaMemcpyDeviceToHost));

          cv::Mat output(numRows(), numCols(), CV_8UC4, (void*)h_outputImage);

          cv::imwrite(output_file.c_str(), output);

          /* Libera memoria */
          cudaFree(d_rgbaImage__);
          cudaFree(d_rgba2Image__);
          cudaFree(d_outputImage__);

      }

  


      break;

    default:
        std::cerr << "Usage: ./global_op -g | -eq | -not  [image path] [gamma -g] " << std::endl;
        std::cerr << "Usage: ./global_op -s | -and | -or  [image1 path] [image2 path] " << std::endl;
        exit(1);
  }





  return 0;
}
