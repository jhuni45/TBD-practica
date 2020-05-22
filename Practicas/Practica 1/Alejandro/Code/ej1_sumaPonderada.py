from cv2 import cv2 as cv

img1 = cv.imread("Practica/Input/field.jpg", 1) 
img2 = cv.imread("Practica/Input/lake.jpg", 1) 

#Suma ponderada "addWeighted"

for i in range(0, 100):
    res = cv.addWeighted(img1, i/100.0, img2, 1-i/100.0, 0.0)
    cv.imshow("Transicion", res)
    cv.waitKey(10)
