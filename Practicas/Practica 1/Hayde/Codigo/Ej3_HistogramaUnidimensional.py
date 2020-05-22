import cv2 as cv
from matplotlib import pyplot as plt
import numpy as np

# Cargamos la Imagen
IMAGEN_A = cv.imread("imagen3.jpg", 1)

gris = cv.cvtColor(IMAGEN_A, cv.COLOR_BGR2GRAY) 
# Grises
cv.imshow("Imagen en Gris", gris)
cv.waitKey(0)

hist = cv.calcHist(images = [gris], channels = [0], mask = None, histSize = [256], ranges = [0, 256])

#Show
plt.title("Histograma - Unidimensional")
plt.plot(hist)
plt.xlim([0,255])
plt.show()