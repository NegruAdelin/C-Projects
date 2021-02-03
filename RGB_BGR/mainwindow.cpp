#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->SchimbaRGB->setEnabled(false);
    ui->Save->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AlegePoza_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("Open Image"), "D:/Kit/wallpaper",
                                                     tr("Image File (*.png, *.jpg)"));
     poza = imread(fileName.toLatin1().data());

     cvtColor(poza, poza, COLOR_BGR2RGB);

     if(poza.data){
         ui->SchimbaRGB->setEnabled(true);
         ui->Save->setEnabled(true);
     }

     QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
     img = img.scaled(img.size().width() / 2, img.size().height() / 2, Qt::IgnoreAspectRatio);

     ui->label->setPixmap(QPixmap::fromImage(img));
     ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_SchimbaRGB_clicked()
{
    cvtColor(poza, poza, COLOR_BGR2RGB);
    QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
    img = img.scaled(img.size().width() / 2, img.size().height() / 2, Qt::IgnoreAspectRatio);

    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
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
