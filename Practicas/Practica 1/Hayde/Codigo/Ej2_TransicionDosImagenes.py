import cv2 as cv

# Cargamos las Imagenes
A = cv.imread("imagen1.jpg", 1); 
B = cv.imread("imagen2.jpg", 1); 

# Transicion
for i in range (0,100):
    res = cv.addWeighted(A, i/100.0, B, 1-i/100.0, 0.0)
    cv.imshow("Transicion", res)
    cv.waitKey(100)
