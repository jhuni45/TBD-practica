import cv2 as cv
from matplotlib import pyplot as plt
import numpy as np

# Cargamos las Imagenes
IMAGEN_A = cv.imread("imagen1.jpg", 1) 
IMAGEN_B = cv.imread("imagen2.jpg", 1) 

# Suma Ponderada 
for i in range(0, 100):
    salida = cv.addWeighted(IMAGEN_A, i/100.0, IMAGEN_B, 1-i/100.0, 0.0)
    cv.imshow("Suma Ponderada", salida)
    cv.waitKey(100)
