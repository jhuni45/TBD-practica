from cv2 import cv2 as cv
import numpy as np

img = cv.imread("Practica/Input/perro.jpg", 1)

#Calcular histograma bidimensional canales R, G


hist = cv.calcHist(images = [img], 
                   channels = [2,1],
                   mask = None,
                   histSize = [64,64],
                   ranges = [0, 256])


# MAT CV_8UC1
pinta = np.zeros((64, 64), dtype = "uint8")

minval, maxval = cv.minMaxLoc(hist) # Para escalar el color entre blanco y negro

for r in range(0,64):
    for g in range(0,64):
        pinta[r][g] = 255 - 255*hist[r][g]/maxval

cv.imshow("Perrito", img)
cv.imshow("Histograma R-G", pinta)

cv.waitKey(0)