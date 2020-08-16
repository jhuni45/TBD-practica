#-------------------------------------------------
#
# Project created by QtCreator 2018-06-19T01:25:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grafica
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    funciones.h

FORMS    += mainwindow.ui

#para el opencv
INCLUDEPATH += /usr/include/opencv #$ pkg-config --cflags opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
