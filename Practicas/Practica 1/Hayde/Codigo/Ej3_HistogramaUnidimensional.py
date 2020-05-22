import cv2 as cv
from matplotlib import pyplot as plt
import numpy as np

# Cargamos la Imagen
IMAGEN_A = cv.imread("imagen3.jpg", 1)
grises = cv.cvtColor(IMAGEN_A, cv.COLOR_BGR2GRAY) 
cv.imshow("Imagen en Gris", grises)
cv.waitKey(0)

# Histograma
histograma = cv.calcHist(images = [grises], channels = [0], mask = None, histSize = [256], ranges = [0, 256])

# Salida
plt.title("Histograma - Unidimensional")
plt.plot(histograma)
plt.xlim([0,255])
plt.show()
