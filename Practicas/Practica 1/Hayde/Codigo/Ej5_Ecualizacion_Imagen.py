import cv2 as cv
from matplotlib import pyplot as plt
import numpy as np

# Cargamos las Imagenes
IMAGEN_A = cv.imread("imagen4.jpg", 1)

# Ecualizacion
gris = cv.cvtColor(IMAGEN_A, cv.COLOR_BGR2GRAY)
histograma = cv.calcHist(images = [gris], channels = [0], mask = None, histSize = [256], ranges = [0, 256])
histograma = histograma * 255.0/cv.norm(histograma, cv.NORM_L1)
LUT = np.zeros((1, 256), dtype = "uint8")
aux = 0.0
for i in range (0,256):	
	LUT[0][i] = aux	
	aux = aux + histograma[i]

# Salida
salida = cv.LUT(IMAGEN_A,LUT)
cv.imshow("Imagen Original", IMAGEN_A)
cv.imshow("Imagen Ecualizada", salida)
cv.waitKey(0)