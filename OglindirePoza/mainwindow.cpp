#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Verticala->setEnabled(false);
    ui->Oglindire->setEnabled(false);
    ui->Orizontala->setEnabled(false);
    ui->Save->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_Verticala_clicked()
{
    flip(poza, poza, -1);
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
    img = img.scaled(img.size().width() / 2, img.size().height() / 2, Qt::IgnoreAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_Orizontala_clicked()
{
    flip(poza, poza, 0);
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
    img = img.scaled(img.size().width() / 2, img.size().height() / 2, Qt::IgnoreAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_Oglindire_clicked()
{
    flip(poza, poza, 1);
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
    img = img.scaled(img.size().width() / 2, img.size().height() / 2, Qt::IgnoreAspectRatio);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("Open Image"), "D:/Kit/wallpaper",
                                                     tr("Image File (*.png, *.jpg)"));
    poza = imread(fileName.toLatin1().data());

    if(poza.data){
        ui->Verticala->setEnabled(true);
        ui->Oglindire->setEnabled(true);
        ui->Orizontala->setEnabled(true);
        ui->Save->setEnabled(true);
    }

    cvtColor(poza, poza, COLOR_BGR2RGB); //Modificarea din BGR in RGB
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888); //Transpunerea in QImage
    img = img.scaled(img.size().width() / 2, img.size().height() / 2, Qt::IgnoreAspectRatio); //Modificarea dimensiunii imaginii

    ui->label->setPixmap(QPixmap::fromImage(img)); //Este folosit pentru adaugarea imaginii
    ui->label->resize(ui->label->pixmap()->size()); //Este folosit pentru modifcarea label-ului
}

void MainWindow::on_Save_clicked()
{
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
    img = img.scaled(img.size().width() / 2, img.size().height() / 2, Qt::IgnoreAspectRatio);

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"),
                                                    QString(),
                                                    tr("Images (*.png)"));
    if (!fileName.isEmpty())
    {
      img.save(fileName);
    }
}
