from cv2 import cv2 as cv
import numpy as np
from matplotlib import pyplot as plt

img = cv.imread("Practica/Input/field.jpg", 1)

#Calcular histograma unidimensional nivel gris

gris = cv.cvtColor(img, cv.COLOR_BGR2GRAY) #conversion gris
cv.imshow("Gris", gris)
cv.waitKey(0)


hist = cv.calcHist(images = [gris], 
                   channels = [0],
                   mask = None,
                   histSize = [256],
                   ranges = [0, 256])

#Gráfico
plt.plot(hist)
plt.xlim([0,255])
plt.show()
