from cv2 import cv2 as cv
import numpy as np

img = cv.imread("Practica/Input/lake.jpg", 1)

#Ecualización Conjunta
gris = cv.cvtColor(img, cv.COLOR_BGR2GRAY) #conversion gris
hist = cv.calcHist(images = [gris], 
                   channels = [0],
                   mask = None,
                   histSize = [256],
                   ranges = [0, 256])

hist *= 255.0/cv.norm(hist, cv.NORM_L1)

# MAT CV_8UC1
lut = np.zeros((1, 256), dtype = "uint8")

acum = 0.0
for i in range (0,256):
    lut[0][i] = acum
    acum += hist[i]

res = cv.LUT(img,lut)

cv.imshow("Entrada", img)
cv.imshow("Ecualizada", res)
cv.waitKey(0)