#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->horizontalSlider->setMaximum(20);
    ui->horizontalSlider->setMinimum(1);
    ui->max->setNum(20);
    ui->min->setNum(1);
    ui->horizontalSlider->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_SelectPicture_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("Alege Poza"), "",
                                                     tr("Image File (*.png, *.jpg)"));
    poza = imread(fileName.toLatin1().data());

    Mat binary;
    cvtColor(poza, binary, COLOR_BGR2GRAY);
    threshold(binary, binary, 120, 255, THRESH_BINARY);

    if(poza.data){
        cvtColor(poza, poza, COLOR_BGR2RGB);
        ui->horizontalSlider->setEnabled(true);

        int w, h;

        if(poza.size().width >= 1080 || poza.size().height >= 1080){
            w = poza.size().width / 6;
            h = poza.size().height / 6;
        }
        else{
            w = poza.size().width / 2;
            h = poza.size().height / 2;
        }

        QImage img = QImage((uchar*) binary.data, binary.cols, binary.rows, binary.step, QImage::Format_Grayscale8);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio);
        ui->normal->setPixmap(QPixmap::fromImage(img));
        ui->normal->resize(ui->normal->pixmap()->size());

        Mat pozaErodata;
        erode(binary, pozaErodata, Mat());

        img =QImage((uchar*) pozaErodata.data, pozaErodata.cols, pozaErodata.rows, pozaErodata.step, QImage::Format_Grayscale8);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio);
        ui->erodata->setPixmap(QPixmap::fromImage(img));
        ui->erodata->resize(ui->erodata->pixmap()->size());

        Mat pozaDilatata;
        dilate(binary, pozaDilatata, Mat());
        img =QImage((uchar*) pozaDilatata.data, pozaErodata.cols, pozaDilatata.rows, pozaDilatata.step, QImage::Format_Grayscale8);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio);
        ui->dilatata->setPixmap(QPixmap::fromImage(img));
        ui->dilatata->resize(ui->dilatata->pixmap()->size());

        Mat inchis;
        morphologyEx(binary, inchis, MORPH_CLOSE, Mat());
        img =QImage((uchar*) inchis.data, inchis.cols, inchis.rows, inchis.step, QImage::Format_Grayscale8);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio);
        ui->inchisa->setPixmap(QPixmap::fromImage(img));
        ui->inchisa->resize(ui->inchisa->pixmap()->size());

        Mat deschisa;
        morphologyEx(binary, deschisa, MORPH_OPEN, Mat());
        img =QImage((uchar*) deschisa.data, deschisa.cols, deschisa.rows, deschisa.step, QImage::Format_Grayscale8);
        img = img.scaled(w, h, Qt::IgnoreAspectRatio);
        ui->deschisa->setPixmap(QPixmap::fromImage(img));
        ui->deschisa->resize(ui->deschisa->pixmap()->size());

        Mat inchis_deschis;
        morphologyEx(inchis, inchis_deschis, MORPH_OPEN, Mat());
        img =QImage((uchar*) inchis_deschis.data, inchis_deschis.cols, inchis_deschis.rows, inchis_deschis.step, QImage::Format_Grayscale8);
        img = img.scaled(w,h, Qt::IgnoreAspectRatio);
        ui->inchis_deschis->setPixmap(QPixmap::fromImage(img));
        ui->inchis_deschis->resize(ui->inchis_deschis->pixmap()->size());
    }
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    int val = ui->horizontalSlider->value();
    ui->min->setNum(val);

    Mat element(val, val, CV_8U, cv::Scalar(1));
    int w, h;

    Mat binary;
    cvtColor(poza, binary, COLOR_BGR2GRAY);
    threshold(binary, binary, 120, 255, THRESH_BINARY);

    if(poza.size().width >= 1080 || poza.size().height >= 1080){
        w = poza.size().width / 6;
        h = poza.size().height / 6;
    }
    else{
        w = poza.size().width / 2;
        h = poza.size().height / 2;
    }

    Mat pozaErodata;
    erode(binary, pozaErodata, element);

    QImage img =QImage((uchar*) pozaErodata.data, pozaErodata.cols, pozaErodata.rows, pozaErodata.step, QImage::Format_Grayscale8);
    img = img.scaled(w, h, Qt::IgnoreAspectRatio);
    ui->erodata->setPixmap(QPixmap::fromImage(img));
    ui->erodata->resize(ui->erodata->pixmap()->size());

    Mat pozaDilatata;
    dilate(binary, pozaDilatata, element);
    img =QImage((uchar*) pozaDilatata.data, pozaErodata.cols, pozaDilatata.rows, pozaDilatata.step, QImage::Format_Grayscale8);
    img = img.scaled(w, h, Qt::IgnoreAspectRatio);
    ui->dilatata->setPixmap(QPixmap::fromImage(img));
    ui->dilatata->resize(ui->dilatata->pixmap()->size());

    Mat inchis;
    morphologyEx(binary, inchis, MORPH_CLOSE, element);
    img =QImage((uchar*) inchis.data, inchis.cols, inchis.rows, inchis.step, QImage::Format_Grayscale8);
    img = img.scaled(w, h, Qt::IgnoreAspectRatio);
    ui->inchisa->setPixmap(QPixmap::fromImage(img));
    ui->inchisa->resize(ui->inchisa->pixmap()->size());

    Mat deschisa;
    morphologyEx(binary, deschisa, MORPH_OPEN, element);
    img =QImage((uchar*) deschisa.data, deschisa.cols, deschisa.rows, deschisa.step, QImage::Format_Grayscale8);
    img = img.scaled(w, h, Qt::IgnoreAspectRatio);
    ui->deschisa->setPixmap(QPixmap::fromImage(img));
    ui->deschisa->resize(ui->deschisa->pixmap()->size());

    Mat inchis_deschis;
    morphologyEx(inchis, inchis_deschis, MORPH_OPEN,element);
    img =QImage((uchar*) inchis_deschis.data, inchis_deschis.cols, inchis_deschis.rows, inchis_deschis.step, QImage::Format_Grayscale8);
    img = img.scaled(w,h, Qt::IgnoreAspectRatio);
    ui->inchis_deschis->setPixmap(QPixmap::fromImage(img));
    ui->inchis_deschis->resize(ui->inchis_deschis->pixmap()->size());
}
