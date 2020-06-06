#include <iostream>
#include "utils.h"
#include <string>
#include <stdio.h>

// Declaramos la funcion que invoca al kernel
void gamma_correction(uchar4 * const d_rgbaImage,
                  uchar4* const d_greyImage, 
                  size_t numRows, size_t numCols, float gamma);

// Incluye las definiciones de las funciones de arriba
#include "preprocess.cpp"

int main(int argc, char **argv) {
  uchar4        *h_rgbaImage, *d_rgbaImage;
  uchar4        *h_outputImage, *d_outputImage;

  std::string input_file;
  std::string input_file2;
  std::string output_file;
  float gamma;
  std::string exercise = std::string(argv[1]);

  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  switch (argc)
  {  
    case 4:
      
      //Caso gamma "-g"
      if( exercise == "-g"  ){
          input_file = std::string(argv[2]);
          output_file = input_file + "_output.jpg";
          gamma = atof(argv[3]);

          // Carga la imagen y nos prepara los punteros para la entrada y  
          // salida de datos
          preProcess(&h_rgbaImage, &h_outputImage, &d_rgbaImage, &d_outputImage, input_file);

          // Invoca al código de kernel para ser llamado.
          gamma_correction(d_rgbaImage, d_outputImage, numRows(), numCols(), gamma);

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

      //Caso ecualización de imagen
      if( exercise == "-eq" ){

      }

      //Caso negación de imagen
      if( exercise == '-not' ){

      }

      
      break;

    case 5:
      //Caso suma de 2 imágenes
      if( exercise == 's' ){

      }

      //Caso operador AND entre 2 imágenes
      if( exercise == '-and' ){

      }

      //Caso operador OR entre 2 imágenes
      if( exercise == '-or' ){

      }



      break;

    default:
        std::cerr << "Usage: ./global_op -g | -eq | -not  [image path] [gamma -g] " << std::endl;
        std::cerr << "Usage: ./global_op -s | -and | -or  [image1 path] [image2 path] " << std::endl;
        exit(1);
  }





  return 0;
}
