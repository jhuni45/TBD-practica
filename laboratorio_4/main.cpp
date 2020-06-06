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
  std::string output_file;
  float gamma;

  //Comprobar que el contexto se inicializa bien
  checkCudaErrors(cudaFree(0));

  switch (argc)
  {
	case 3:
	  input_file = std::string(argv[1]);
	  output_file = input_file + "_output.jpg";
    gamma = atof(argv[2]);
	  break;

	default:
      std::cerr << "Usage: ./global_op input_file gamma" << std::endl;
      exit(1);
  }


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


  return 0;
}
