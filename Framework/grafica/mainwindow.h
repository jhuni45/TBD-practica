#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include <vector>
#include <math.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;





namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    int opcionB; //opcion de botton
    Mat imagenCV;
    Mat imagenCV1;
    Mat imagenCV2;
    Mat imagenCV12;
    Mat imagenCV_alter;
    Mat imagenCV_histo;
    Mat imagenCVfc;
    Mat imagenCVfcres;
    Mat imagenCVHisto_ini;
    Mat imagenCVHisto_fin;
//    Mat imagenCV;



private slots:
    void on_Abrir_clicked();

    void on_Restaurar_clicked();

    void on_Scroll_sliderMoved(int position);

    void on_Opcion_activated(int index);

    void on_abrir1_clicked();

    void on_abrir2_clicked();

    void on_comboBox_activated(int index);

    void on_Abrirfc_clicked();

    void on_pushButton_clicked();

    void on_abrirTransHis_clicked();

    void on_Ecualizar_clicked();

    void on_Opcion_LOT_activated(int index);

    void on_comboBox_3_activated(int index);

    void on_comboBox_4_activated(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWindow *ui;
};




#endif // MAINWINDOW_H
