from cv2 import cv2 as cv
import numpy as np

img = cv.imread("Practica/Input/field.jpg", 1)

#Transformación gamma

#Convertir a float
im32F = img.astype(np.float32)/255

#Modificación del gamma
power = pow(im32F,2)

#Convertir a unsigned 8 bit 
power = power * 255
img3U = power.astype(np.uint8)

cv.imshow("Original", img)
cv.imshow("Gamma", img3U)
cv.waitKey(0)

