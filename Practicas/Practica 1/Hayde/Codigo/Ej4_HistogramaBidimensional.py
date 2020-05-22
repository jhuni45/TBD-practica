import cv2 as cv

# Cargamos las Imagenes
IMAGEN_A = cv.imread("imagen1.jpg", 1); 
IMAGEN_B = cv.imread("imagen2.jpg", 1); 

# Transicion
for i in range (0,100):
    res = cv.addWeighted(IMAGEN_A, i/100.0, IMAGEN_B, 1-i/100.0, 0.0)
    cv.imshow("Transicion", res)
    cv.waitKey(100)
