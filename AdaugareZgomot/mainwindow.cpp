#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SnowSlider->setEnabled(false);
    ui->Salveaza->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zgomot(Mat &poza, int n){
    for(int k = 0; k < n; k++){
        int i = rand()%poza.size().height;
        int j = rand()%poza.size().width;

        if(poza.channels() == 1){
            poza.at<uchar>(i, j) = 255;
        }
        else{
            if(poza.channels() == 3){
                poza.at<Vec3b>(i,j)[0] = 255;
                poza.at<Vec3b>(i, j)[1] = 255;
                poza.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
}

void MainWindow::on_AlegePoza_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("Open Image"), "D:/Kit/wallpaper",
                                                     tr("Image File (*.png, *.jpg)"));
     poza = imread(fileName.toLatin1().data());

     if(poza.data){
        min = 0, max = poza.size().width * poza.size().height / 10;

        ui->Salveaza->setEnabled(true);
        ui->SnowSlider->setEnabled(true);
        ui->SnowSlider->setMinimum(0);
        ui->SnowSlider->setMaximum(poza.size().width * poza.size().height / 10);
        ui->minim->setNum(min);
        ui->maxim->setNum(max);

        cvtColor(poza, poza, COLOR_BGR2RGB);
        QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(img));
        ui->label->resize(ui->label->pixmap()->size());
     }
}

void MainWindow::on_SnowSlider_actionTriggered(int action)
{
    min = ui->SnowSlider->value();
    ui->minim->setNum(min);

    poza.copyTo(pozaAux);
    zgomot(pozaAux, min);

    QImage img = QImage((uchar*) pozaAux.data, pozaAux.cols, pozaAux.rows, pozaAux.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_Salveaza_clicked()
{
    QImage img = QImage((uchar*) pozaAux.data, pozaAux.cols, pozaAux.rows, pozaAux.step, QImage::Format_RGB888);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));
    if (!fileName.isEmpty())
    {
      img.save(fileName);
    }
}
