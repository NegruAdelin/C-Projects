#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->thresholdSlider->setEnabled(false);
    ui->dstSlider->setEnabled(false);
    ui->label_binar->setVisible(false);
    ui->label_combinata->setVisible(false);
    ui->label_originala->setVisible(false);
    ui->Save->setEnabled(false);
    ui->dstSlider->setMinimum(0);
    ui->dstSlider->setMaximum(255);
    ui->thresholdSlider->setMinimum(0);
    ui->thresholdSlider->setMaximum(255);
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

void MainWindow::pondre_binara(Mat picture){
    Mat grayscal;
    QImage img;

    poza_combinata = NULL;
    poza_binara = NULL;

    cvtColor(picture, grayscal, COLOR_BGR2GRAY);
    threshold(grayscal, poza_binara, ui->dstSlider->value(), ui->thresholdSlider->value(), THRESH_BINARY);

    img = QImage((uchar*) poza_binara.data, poza_binara.cols, poza_binara.rows, poza_binara.step, QImage::Format_Grayscale8);
    img = img.scaled(w, h);

    ui->poza_binara->setPixmap(QPixmap::fromImage(img));
    ui->poza_binara->resize(ui->poza_binara->pixmap()->size());

    poza.copyTo(poza_combinata, poza_binara);

    img = QImage((uchar*) poza_combinata.data, poza_combinata.cols, poza_combinata.rows, poza_combinata.step, QImage::Format_BGR888);
    img = img.scaled(w, h);

    ui->poza_combinata->setPixmap(QPixmap::fromImage(img));
    ui->poza_combinata->resize(ui->poza_combinata->pixmap()->size());
}

void MainWindow::on_poza_clicked()
{
    QImage img;
    QString filepath = QFileDialog::getOpenFileName(this, tr("Alege Poza"), "",
                                                   tr("Image File (*.png, *.jpg, *.PNG, *.JPG)"));
    poza = imread(filepath.toLatin1().data());

    if(poza.data && filepath.toStdString() != ""){
        set_height_width(poza);

        img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_BGR888);
        img = img.scaled(w, h);

        ui->poza_originala->setPixmap(QPixmap::fromImage(img));
        ui->poza_originala->resize(ui->poza_originala->pixmap()->size());

        if(!on){
            ui->thresholdSlider->setEnabled(true);
            ui->Save->setEnabled(true);
            ui->dstSlider->setEnabled(true);
            ui->label_binar->setVisible(true);
            ui->label_combinata->setVisible(true);
            ui->label_originala->setVisible(true);
            on = true;
        }

        ui->dstSlider->setValue(50);
        ui->thresholdSlider->setValue(255);
        ui->maxDst->setNum(ui->dstSlider->maximum());
        ui->maxThreshold->setNum(ui->thresholdSlider->maximum());
        ui->minDst->setNum(ui->dstSlider->value());
        ui->minThreshold->setNum(ui->thresholdSlider->value());

        pondre_binara(poza);
    }
}

void MainWindow::on_dstSlider_actionTriggered(int action)
{
    ui->minDst->setNum(ui->dstSlider->value());
    pondre_binara(poza);
}

void MainWindow::on_thresholdSlider_actionTriggered(int action)
{
    ui->minThreshold->setNum(ui->thresholdSlider->value());
    pondre_binara(poza);
}

void MainWindow::on_Save_clicked()
{
    QString path_save = QFileDialog::getSaveFileName(this, tr("Salveaza Poza Binara"), ""
                                                     , tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));


    if(poza.data && path_save.toStdString() != ""){
        imwrite(path_save.toStdString(), poza_binara);
    }

    path_save = QFileDialog::getSaveFileName(this, tr("Salveaza Poza Combinata"), ""
                                                         , tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));


    if(poza.data && path_save.toStdString() != ""){
        imwrite(path_save.toStdString(), poza_combinata);
    }
}
