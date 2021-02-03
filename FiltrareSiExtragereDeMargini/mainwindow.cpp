#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Save->setEnabled(false);
    ui->threshold1->setEnabled(false);
    ui->threshold2->setEnabled(false);
    ui->Spatiu->setEnabled(false);
    ui->Diametru->setEnabled(false);
    ui->Culoare->setEnabled(false);

    ui->labelPoza1->setVisible(false);
    ui->labelPoza2->setVisible(false);
    ui->labelPoza3->setVisible(false);

    ui->threshold1->setMaximum(255);
    ui->threshold1->setMinimum(0);

    ui->threshold2->setMaximum(255);
    ui->threshold2->setMinimum(0);

    ui->Spatiu->setMaximum(200);
    ui->Spatiu->setMinimum(0);

    ui->Diametru->setMaximum(50);
    ui->Diametru->setMinimum(0);

    ui->Culoare->setMaximum(200);
    ui->Culoare->setMinimum(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_height_width(Mat picture){
    h = poza.rows;
    w = poza.cols;

    if(h >= 1080 || w >= 1080){
        h /= 6;
        w /= 6;
    }
    else{
        h /= 2;
        w /= 2;
    }
}

void MainWindow::filtru(Mat picture){
    int thre1, thre2, culoare, spatiu, diametru;

    thre1 = ui->threshold1->value();
    thre2 = ui->threshold2->value();
    culoare = ui->Culoare->value();
    spatiu = ui->Spatiu->value();
    diametru = ui->Diametru->value();

    bilateralFilter(picture, aux, diametru, culoare, spatiu);

    Canny(aux, canny, thre1, thre2);

    QImage img = QImage((uchar*) canny.data, canny.cols, canny.rows, canny.step, QImage::Format_Grayscale8);
    img = img.scaled(w, h);

    ui->CannyAplicat->setPixmap(QPixmap::fromImage(img));
    ui->CannyAplicat->resize(ui->CannyAplicat->pixmap()->size());

    img = QImage((uchar*) aux.data, aux.cols, aux.rows, aux.step, QImage::Format_BGR888);
    img = img.scaled(w, h);

    ui->FiltruAplicat->setPixmap(QPixmap::fromImage(img));
    ui->FiltruAplicat->resize(ui->FiltruAplicat->pixmap()->size());
    canny.copyTo(saveCanny);
    aux.copyTo(saveFiltru);
}

void MainWindow::on_Image_clicked()
{
    QImage img;
    QString filepath = QFileDialog::getOpenFileName(this, tr("Alege Poza"), "",
                                                   tr("Image File (*.png, *.jpg, *.PNG, *.JPG)"));

    poza = imread(filepath.toLatin1().data());

    if(poza.data){
        set_height_width(poza);
        filtru(poza);

        img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_BGR888);
        img = img.scaled(w, h);
        ui->Originala->setPixmap(QPixmap::fromImage(img));
        ui->Originala->resize(ui->Originala->pixmap()->size());

        ui->minCuloare->setNum(0);
        ui->minDiametru->setNum(0);
        ui->minSpatiu->setNum(0);
        ui->minThreshold1->setNum(0);
        ui->minThreshold2->setNum(0);
        ui->maxCuloare->setNum(ui->Culoare->maximum());
        ui->maxDiametru->setNum(ui->Diametru->maximum());
        ui->maxSpatiu->setNum(ui->Spatiu->maximum());
        ui->maxThreshold1->setNum(ui->threshold1->maximum());
        ui->maxThreshold2->setNum(ui->threshold2->maximum());
        ui->Diametru->setValue(10);
        ui->Culoare->setValue(100);
        ui->Spatiu->setValue(200);
        ui->threshold1->setValue(100);
        ui->threshold2->setValue(200);
        ui->minCuloare->setNum(ui->Culoare->value());
        ui->minSpatiu->setNum(ui->Spatiu->value());
        ui->minDiametru->setNum(ui->Diametru->value());
        ui->minThreshold1->setNum(ui->threshold1->value());
        ui->minThreshold2->setNum(ui->threshold2->value());
        ui->CannyLabel->setVisible(true);

        if(!on){
            ui->Save->setEnabled(true);
            ui->Spatiu->setEnabled(true);
            ui->Diametru->setEnabled(true);
            ui->Culoare->setEnabled(true);
            ui->threshold1->setEnabled(true);
            ui->threshold2->setEnabled(true);

            ui->labelPoza1->setVisible(true);
            ui->labelPoza2->setVisible(true);
            ui->labelPoza3->setVisible(true);
            on = true;
        }
    }
}

void MainWindow::on_Save_clicked()
{
    QString path_save = QFileDialog::getSaveFileName(this, tr("Salveaza Poza Canny"), ""
                                                     , tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));


    if(poza.data && path_save.toStdString() != ""){
        imwrite(path_save.toStdString(), saveCanny);
    }

    path_save = QFileDialog::getSaveFileName(this, tr("Salveaza Poza Filtru"), ""
                                                         , tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));


    if(poza.data && path_save.toStdString() != ""){
        imwrite(path_save.toStdString(), saveFiltru);
    }
}

void MainWindow::on_Culoare_sliderReleased()
{
    filtru(poza);
}

void MainWindow::on_Diametru_sliderReleased()
{
    filtru(poza);
}

void MainWindow::on_Spatiu_sliderReleased()
{
    filtru(poza);
}

void MainWindow::on_threshold1_sliderReleased()
{
    filtru(poza);
}

void MainWindow::on_threshold2_sliderReleased()
{
    filtru(poza);
}

void MainWindow::on_threshold1_actionTriggered(int action)
{
    ui->minThreshold1->setNum(ui->threshold1->value());
}

void MainWindow::on_threshold2_actionTriggered(int action)
{
    ui->minThreshold2->setNum(ui->threshold2->value());
}

void MainWindow::on_Diametru_actionTriggered(int action)
{
    ui->minDiametru->setNum(ui->Diametru->value());
}

void MainWindow::on_Culoare_actionTriggered(int action)
{
    ui->minCuloare->setNum(ui->Culoare->value());
}

void MainWindow::on_Spatiu_actionTriggered(int action)
{
   ui->minSpatiu->setNum(ui->Spatiu->value());
}
