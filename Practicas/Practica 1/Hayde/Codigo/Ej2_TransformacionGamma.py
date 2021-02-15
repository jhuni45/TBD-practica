import cv2 as cv
from matplotlib import pyplot as plt
import numpy as np

# Cargamos la Imagen
IMAGEN_A = cv.imread("imagen2.jpg", 1)

# Tranasformacion Gamma
im32 = IMAGEN_A.astype (np.float32) / 255
imagen = pow (im32 , 0.5)
imagen = imagen * 255

# Salida
salida = imagen.astype(np.uint8)
cv.imshow("Imagen Original", IMAGEN_A)
cv.imshow("Imagen Gamma", salida)
cv.waitKey(0)