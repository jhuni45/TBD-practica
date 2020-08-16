#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



Mat todownload, todownloadhisto;

Mat get_histo(Mat& src){
    int bins = 256;
    int hist_size[] = {bins};
    float range[] = { 0, 256 };
    const float* ranges[] = { range};
    MatND hist_r,hist_g,hist_b;
    int channels_r[] = {0};

    calcHist( &src, 1, channels_r, Mat(), // do not use mask
        hist_r, 1, hist_size, ranges,
        true, // the histogram is uniform
        false );

    int channels_g[] = {1};
    calcHist( &src, 1, channels_g, Mat(), // do not use mask
        hist_g, 1, hist_size, ranges,
        true, // the histogram is uniform
        false );

    int channels_b[] = {2};
    calcHist( &src, 1, channels_b, Mat(), // do not use mask
        hist_b, 1, hist_size, ranges,
        true, // the histogram is uniform
        false );
    double max_val_r,max_val_g,max_val_b;
    minMaxLoc(hist_r, 0, &max_val_r, 0, 0);
    minMaxLoc(hist_g, 0, &max_val_g, 0, 0);
    minMaxLoc(hist_b, 0, &max_val_b, 0, 0);
    int scale = 1;
    int hist_height=256;
    Mat hist_img = Mat::zeros(hist_height,bins*3, CV_8UC3);
    for(int i=0;i<bins;i++)
    {
        float bin_val_r = hist_r.at<float>(i);
        float bin_val_g = hist_g.at<float>(i);
        float bin_val_b = hist_b.at<float>(i);
        int intensity_r = cvRound(bin_val_r*hist_height/max_val_r);
        int intensity_g = cvRound(bin_val_g*hist_height/max_val_g);
        int intensity_b = cvRound(bin_val_b*hist_height/max_val_b);
        rectangle(hist_img,Point(i*scale,hist_height-1),
            Point((i+1)*scale - 1, hist_height - intensity_r),
            CV_RGB(255,0,0));

        rectangle(hist_img,Point((i+bins)*scale,hist_height-1),
            Point((i+bins+1)*scale - 1, hist_height - intensity_g),
            CV_RGB(0,255,0));

        rectangle(hist_img,Point((i+bins*2)*scale,hist_height-1),
            Point((i+bins*2+1)*scale - 1, hist_height - intensity_b),
            CV_RGB(0,0,255));
    }
    todownload=src;
    return hist_img;
}


void operacionAritmetica(Mat& imagen , int val,  int ope){
     if ( !imagen.data )
    {
        printf("No image data \n");
        return ;
    }
    int f = imagen.rows;
    int c = imagen.cols;
//    cout<<"\nfila: "<<f<<"\ncol: "<<c<<endl;
    Vec3b* imgrow;
    if(ope == 0) {//sumar
        for(int i = 0; i< f; i++){
            imgrow= imagen.ptr<Vec3b>(i);
            for(int j = 0; j < c ; j++){
                imgrow[j][0] = saturate_cast<uchar>(imgrow[j][0] + val);
                imgrow[j][1] = saturate_cast<uchar>(imgrow[j][1] + val);
                imgrow[j][2] = saturate_cast<uchar>(imgrow[j][2] + val);

            }
        }
    }
    else if(ope == 1){//restar
        for(int i = 0; i< f; i++){
            imgrow= imagen.ptr<Vec3b>(i);
            for(int j = 0; j < c ; j++){
                imgrow[j][0] = saturate_cast<uchar>(imgrow[j][0] - val);
                imgrow[j][1] = saturate_cast<uchar>(imgrow[j][1] - val);
                imgrow[j][2] = saturate_cast<uchar>(imgrow[j][2] - val);
            }
        }
    }
    else if(ope == 2){//multiplicar
         float value = ((val)/200.0);//0.0-2.0
        for(int i = 0; i< f; i++){
            imgrow= imagen.ptr<Vec3b>(i);
            for(int j = 0; j < c ; j++){
                imgrow[j][0] = saturate_cast<uchar>(imgrow[j][0] * value);
                imgrow[j][1] = saturate_cast<uchar>(imgrow[j][1] * value);
                imgrow[j][2] = saturate_cast<uchar>(imgrow[j][2] * value);
            }
        }
    }
    else if(ope == 3){//dividir
        float value2 = ((val)/200.0);//0.0-2.0
        for(int i = 0; i< f; i++){
            imgrow= imagen.ptr<Vec3b>(i);
            for(int j = 0; j < c ; j++){
                imgrow[j][0] = saturate_cast<uchar>(imgrow[j][0] / value2);
                imgrow[j][1] = saturate_cast<uchar>(imgrow[j][1] / value2);
                imgrow[j][2] = saturate_cast<uchar>(imgrow[j][2] / value2);
            }
        }
    }
    else{
        cout<<"\nOperacion no definida\n";
        return;
    }
//    cout<<"terminado";

    //namedWindow("OperacionAritmetica", WINDOW_AUTOSIZE );
    //imshow("Operacion", imagen);
//    waitKey(0);
    todownload=imagen;

}

void calcular_histograma(Mat his){


}
void MainWindow::on_Abrir_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("chose"), "", tr("Images (*.bmp)"));
    if(QString::compare(filename, QString() ) != 0){
       QImage image;
       bool valido = image.load(filename);

       if(valido){
           image = image.scaledToWidth( ui->imagen_ini->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->imagen_ini->setPixmap(QPixmap::fromImage(image));
           //copiando a Mat
           imagenCV = imread(filename.toUtf8().constData());

           imagenCV_alter = imagenCV;

           cv::Mat temp(imagenCV_alter.cols,imagenCV_alter.rows,imagenCV_alter.type()); // make the same cv::Mat
           cvtColor(imagenCV_alter,temp ,COLOR_BGR2RGB);
           QImage alter= QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
           alter = alter.scaledToWidth( ui->imagen_fin->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->imagen_fin->setPixmap(QPixmap::fromImage(alter));

//           mostrar el histograma de  imagenCV_alter
           imagenCV_histo = get_histo(imagenCV_alter);
           cv::Mat temp_h(imagenCV_histo.cols,imagenCV_histo.rows,imagenCV_histo.type()); // make the same cv::Mat
           cvtColor(imagenCV_histo,temp_h ,COLOR_BGR2RGB);
           QImage hist= QImage((uchar*) temp_h.data, temp_h.cols, temp_h.rows, temp_h.step, QImage::Format_RGB888);
           hist = hist.scaledToWidth( ui->histograma->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->histograma->setPixmap(QPixmap::fromImage(hist));
           todownload=temp_h;
       }
       else {
           //erro de abrir
       }
    }
}

void MainWindow::on_Restaurar_clicked()
{
//    imagenCV_alter = imagenCV;
    imagenCV_alter  =imagenCV.clone();
}



void MainWindow::on_Scroll_sliderMoved(int position)
{
    imagenCV_alter = imagenCV;
    cout <<"**___"<< position<<endl;
     operacionAritmetica(imagenCV_alter, position, opcionB);

    cv::Mat temp(imagenCV_alter.cols,imagenCV_alter.rows,imagenCV_alter.type()); // make the same cv::Mat
    cvtColor(imagenCV_alter,temp ,COLOR_BGR2RGB);

    QImage alter= QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    alter = alter.scaledToWidth( ui->imagen_fin->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
    ui->imagen_fin->setPixmap(QPixmap::fromImage(alter));

    //mostrar histograma
    imagenCV_histo = get_histo(imagenCV_alter);
    cv::Mat temp_h(imagenCV_histo.cols,imagenCV_histo.rows,imagenCV_histo.type()); // make the same cv::Mat
    cvtColor(imagenCV_histo,temp_h ,COLOR_BGR2RGB);
    QImage hist= QImage((uchar*) temp_h.data, temp_h.cols, temp_h.rows, temp_h.step, QImage::Format_RGB888);
    hist = hist.scaledToWidth( ui->histograma->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
    ui->histograma->setPixmap(QPixmap::fromImage(hist));
    todownloadhisto=temp_h;

}

void MainWindow::on_Opcion_activated(int index)
{
    opcionB = index;
    ui->Scroll->scroll(0,0); // = 0;

}






void MainWindow::on_abrir1_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("chose"), "", tr("Images (*.bmp)"));
    if(QString::compare(filename, QString() ) != 0){
       QImage image;
       bool valido = image.load(filename);

       if(valido){
           image = image.scaledToWidth( ui->imagen1->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->imagen1->setPixmap(QPixmap::fromImage(image));
           //copiando a Mat
           imagenCV1 = imread(filename.toUtf8().constData());
       }
       else {
           //erro de abrir
       }
    }
}

void MainWindow::on_abrir2_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("chose"), "", tr("Images (*.bmp)"));
    if(QString::compare(filename, QString() ) != 0){
       QImage image;
       bool valido = image.load(filename);

       if(valido){
           image = image.scaledToWidth( ui->imagen2->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->imagen2->setPixmap(QPixmap::fromImage(image));
           //copiando a Mat
           imagenCV2 = imread(filename.toUtf8().constData());
       }
       else {
           //erro de abrir
       }
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    if(index == 0){//sumar
        add(imagenCV1, imagenCV2, imagenCV12, noArray(), -1);
    }
    else if(index == 1){//restar
        subtract(imagenCV1, imagenCV2, imagenCV12, noArray(), -1);
    }
    else if(index == 2){//multiplicar
        multiply(imagenCV1, imagenCV2, imagenCV12, 1.0f, -1);
    }
    else if(index == 3){//dividir
        divide(imagenCV1, imagenCV2, imagenCV12, 1.0f, -1);
    }
    cv::Mat temp(imagenCV12.cols,imagenCV12.rows,imagenCV12.type()); // make the same cv::Mat
    cvtColor(imagenCV12,temp ,COLOR_BGR2RGB);
    QImage alter= QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    alter = alter.scaledToWidth( ui->imagen12->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
    ui->imagen12->setPixmap(QPixmap::fromImage(alter));
    todownload=temp;
}

void MainWindow::on_Abrirfc_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("chose"), "", tr("Images (*.bmp)"));
    if(QString::compare(filename, QString() ) != 0){
       QImage image;
       bool valido = image.load(filename);

       if(valido){
           image = image.scaledToWidth( ui->imagenfc->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->imagenfc->setPixmap(QPixmap::fromImage(image));
           //copiando a Mat
           imagenCVfc = imread(filename.toUtf8().constData());

           imagenCVfcres = imagenCVfc;
           cv::Mat temp(imagenCVfcres.cols,imagenCVfcres.rows,imagenCVfcres.type()); // make the same cv::Mat
           cvtColor(imagenCVfcres,temp ,COLOR_BGR2RGB);
           QImage alter= QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
           alter = alter.scaledToWidth( ui->imagenfcres->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->imagenfcres->setPixmap(QPixmap::fromImage(alter));

       }
       else {
           //erro de abrir
       }
    }
}

void MainWindow::on_pushButton_clicked()
{
    Mat kernel = (Mat_<char>(3,3) <<
                                    0, -1, 0,
                                    -1, 5, -1,
                                    0, -1, 0);
       filter2D(imagenCVfc, imagenCVfcres, -1, kernel, Point(-1, -1), 0, BORDER_DEFAULT);
       cv::Mat temp(imagenCVfcres.cols,imagenCVfcres.rows,imagenCVfcres.type()); // make the same cv::Mat
       cvtColor(imagenCVfcres,temp ,COLOR_BGR2RGB);
       QImage alter= QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
       alter = alter.scaledToWidth( ui->imagenfcres->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
       ui->imagenfcres->setPixmap(QPixmap::fromImage(alter));
       todownload=temp;
}

void MainWindow::on_abrirTransHis_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("chose"), "", tr("Images (*.bmp)"));
    if(QString::compare(filename, QString() ) != 0){
       QImage image;
       bool valido = image.load(filename);

       if(valido){
           image = image.scaledToWidth( ui->transHisto_ini->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->transHisto_ini->setPixmap(QPixmap::fromImage(image));
           //copiando a Mat
           imagenCVHisto_ini = imread(filename.toUtf8().constData());

           imagenCVHisto_fin = imagenCVHisto_ini;
           cv::Mat temp(imagenCVHisto_fin.cols,imagenCVHisto_fin.rows,imagenCVHisto_fin.type()); // make the same cv::Mat
           cvtColor(imagenCVHisto_fin,temp ,COLOR_BGR2RGB);
           QImage alter= QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
           alter = alter.scaledToWidth( ui->transHisto_fin->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
           ui->transHisto_fin->setPixmap(QPixmap::fromImage(alter));
           todownload=temp;
       }
       else {
           //erro de abrir
       }
    }
}


void MainWindow::on_Ecualizar_clicked()
{
    Mat src = imagenCVHisto_ini;
    Mat dst;

    cvtColor( src, src, COLOR_BGR2GRAY );

    /// Apply Histogram Equalization
    equalizeHist( src, dst);
    cv::Mat temp(dst.cols,dst.rows,dst.type()); // make the same cv::Mat
    cvtColor(dst,temp ,COLOR_GRAY2RGB);
    QImage alter= QImage((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    alter = alter.scaledToWidth( ui->transHisto_fin->width() , Qt::SmoothTransformation );//para mostrar la imagen con tamanio
    ui->transHisto_fin->setPixmap(QPixmap::fromImage(alter));
    todownload=temp;
}

void MainWindow::on_Opcion_LOT_activated(int index)
{
    Mat src = imagenCVfc;
    int m=20;
    if(index == 0){
        /// *** TRANSFORMATION PERSPECTIVE ***
        double w= src.size().width, h= src.size().height;
        Mat pt1(1, 4, CV_32FC2); // Cuatro puntos en el origen
        pt1.at<Vec2f>(0,0)= Vec2f(0, 0);
        pt1.at<Vec2f>(0,1)= Vec2f(w, 0);
        pt1.at<Vec2f>(0,2)= Vec2f(w, h);
        pt1.at<Vec2f>(0,3)= Vec2f(0, h);
        Mat pt2(1, 4, CV_32FC2); // Cuatro puntos en el destino
        pt2.at<Vec2f>(0,0)= Vec2f(w*0.3, 0);
        pt2.at<Vec2f>(0,1)= Vec2f(w*0.7, 0);
        pt2.at<Vec2f>(0,2)= Vec2f(w, h);
        pt2.at<Vec2f>(0,3)= Vec2f(0, h);
        Mat c= getPerspectiveTransform(pt1, pt2);
        Mat resultado;
        warpPerspective(src, resultado, c, src.size());
        imshow( "perspective", resultado );
        waitKey(0);
        todownload=resultado;
    }
    else if(index == 1){
        /// *** CRISTALIZED

        Mat mapa1(src.size(), CV_32FC1);
        Mat mapa2(src.size(), CV_32FC1);
        for (int y= 0; y<src.size().height; y++)
            for (int x= 0; x<src.size().width; x++) {
            mapa1.at<float>(y, x)= x - x%m + y%m; // Mapa 1 cambiado
            mapa2.at<float>(y, x)= y - y%m + x%m; // Mapa 2 cambiado
            }
        Mat resultado;
        remap(src, resultado, mapa1, mapa2, INTER_NEAREST);
        imshow( "acristalado", resultado );
        waitKey(0);
        todownload=resultado;

    }
    else if(index == 2){
        /// *** REMAP
        Mat mapa1(src.size(), CV_32FC1);
        Mat mapa2(src.size(), CV_32FC1);
        for (int y= 0; y<src.size().height; y++)
        for (int x= 0; x<src.size().width; x++) {
        mapa1.at<float>(y, x)= x+rand()%(2*m+1) - m; // Mapa 1
        mapa2.at<float>(y, x)= y+rand()%(2*m+1) - m; // Mapa 2
        }
        Mat resultado;
        remap(src, resultado, mapa1, mapa2, INTER_NEAREST);
        imshow( "remap", resultado );
        waitKey(0);
        todownload=resultado;
    }
}

void Rotar(Mat imagen, Mat &salida, double angulo, double escala= 1){
    double w= imagen.size().width, h= imagen.size().height;
    double sa= sin(angulo*M_PI/180), ca= cos(angulo*M_PI/180);
    double cx= -w/2*ca-h/2*sa, cy= w/2*sa-h/2*ca;
    sa= fabs(sa);
    ca= fabs(ca);
    Size tam((w*ca+h*sa)*escala, (h*ca+w*sa)*escala);
    Mat M= getRotationMatrix2D(Point2f(0,0), angulo, escala);
    M.at<double>(0,2)= tam.width/2+cx*escala;
    M.at<double>(1,2)= tam.height/2+cy*escala;
    warpAffine(imagen, salida, M, tam);
}

void MainWindow::on_comboBox_3_activated(int index)
{
    Mat src = imagenCVfc;
    int flipCode=1;
    int angulo=30;
    int value=45;
    Mat dst;
    if(index == 0){
        cv::resize(src, src, Size(), 2, 1);
        imshow("zoom2x", src);
        waitKey(0);
        todownload=src;
    }

    else if(index == 1){
        flip(src, dst, flipCode);
        imshow("flip", dst);
        waitKey(0);
        todownload=dst;
    }
    else if(index == 2){
        Rotar(src,dst, angulo);
        imshow("rotacion", dst);
        waitKey(0);
        todownload=dst;
    }
    else if (index == 3){
        double inc= tan(value*M_PI/180.0);
        Mat c= (Mat_<double>(2, 3) << 1,  inc,  -inc*src.size().height/2.0, 0,  1,   0 );
        warpAffine(src, src, c, src.size());
        imshow("inclinacion", src);
        waitKey(0);
        todownload=src;
    }
    else if (index == 4 ){
        Mat pt1(1, 3, CV_32FC2);
        pt1.at<Vec2f>(0,0)= Vec2f(0, 0);
        pt1.at<Vec2f>(0,1)= Vec2f(100, 0);
        pt1.at<Vec2f>(0,2)= Vec2f(100, 100);
        Mat pt2(1, 3, CV_32FC2);
        pt2.at<Vec2f>(0,0)= Vec2f(10, 20);
        pt2.at<Vec2f>(0,1)= Vec2f(80, 40);
        pt2.at<Vec2f>(0,2)= Vec2f(20, 70);
        Mat c= getAffineTransform(pt1, pt2);
        warpAffine(src, src, c, src.size());
        imshow("affine_transform", src);
        waitKey(0);
        todownload=src;
    }
}

void MinLocal(Mat entrada, Mat &salida, int ancho, int alto){
    erode(entrada, salida, Mat::ones(alto, ancho, CV_8U),Point(-1,-1), 1, BORDER_REPLICATE);
}

void MaxLocal(Mat entrada, Mat &salida, int ancho, int alto){
    dilate(entrada, salida, Mat::ones(alto, ancho, CV_8U),Point(-1,-1), 1, BORDER_REPLICATE);
}

void MainWindow::on_comboBox_4_activated(int index)
{
    Mat src = imagenCVfc;
    if (index == 0 ){
        Mat salida1, salida2;
        Mat kernelPerfilado= (Mat_<float>(3, 3) << -1, -1, -1,-1, 9, -1,-1, -1, -1);
        filter2D(src, salida1, CV_8U, kernelPerfilado);
        Mat kernelDerivada= (Mat_<float>(3, 3) << -2, -1, 0,  -1, 0, 1, 0, 1, 2);
        filter2D(src, salida2, CV_8U, kernelDerivada, Point(-1,-1), 128);
        imshow("canny ", salida2);
        waitKey(0);
        todownload=salida2;
    }
    else if (index ==1 ){
        Mat gris, bordes;
        cvtColor(src, gris, COLOR_BGR2GRAY);
        Canny(gris, bordes, 100, 60);
        imshow("canny ", bordes);
        waitKey(0);
        todownload=bordes;
    }
    else if (index ==2){
        Mat lap, suma, gray;
        GaussianBlur( src, src, Size(3, 3), 0, 0, BORDER_DEFAULT );
        cvtColor( src, gray, COLOR_BGR2GRAY );
        //Laplacian(img, lap, CV_16S);
        Laplacian(gray, suma, CV_16S, 3, 1, 0, BORDER_DEFAULT );

        convertScaleAbs( suma, lap );
        imshow("laplace ", lap);
        waitKey(0);
        todownload=lap;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    imwrite("/home/jhunior/Escritorio/output.jpg",todownload);
}

void MainWindow::on_pushButton_4_clicked()
{
    imwrite("/home/jhunior/Escritorio/output.jpg",todownload);
    imwrite("/home/jhunior/Escritorio/histograma.jpg",todownloadhisto);

}

void MainWindow::on_pushButton_5_clicked()
{
     imwrite("/home/jhunior/Escritorio/output.jpg",todownload);
}

void MainWindow::on_pushButton_6_clicked()
{
     imwrite("/home/jhunior/Escritorio/output.jpg",todownload);
}
