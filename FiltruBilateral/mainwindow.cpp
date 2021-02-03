#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->DiametruVecinatate->setEnabled(false);
    ui->Spatiu->setEnabled(false);
    ui->Save->setEnabled(false);
    ui->DiametruVecinatate->setMinimum(1);
    ui->DiametruVecinatate->setMaximum(50);
    ui->Culoare->setEnabled(false);
    ui->Culoare->setMinimum(1);
    ui->Culoare->setMaximum(200);
    ui->Spatiu->setMinimum(1);
    ui->Spatiu->setMaximum(200);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ChooseFile_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("Poza"), "",
                                                     tr("Image File (*.png, *.jpg)"));
    path = fileName.toStdString();
    poza = imread(fileName.toLatin1().data());

    if(poza.data){
        ui->DiametruVecinatate->setEnabled(true);
        ui->Spatiu->setEnabled(true);
        ui->Save->setEnabled(true);
        ui->Culoare->setEnabled(true);
        ui->minCuloare->setNum(0);
        ui->maxCuloare->setNum(200);
        ui->minSpatiu->setNum(0);
        ui->maxSpatiu->setNum(200);
        ui->minDiametru->setNum(0);
        ui->maxDiametru->setNum(50);
        bilateral();
    }
}

void MainWindow::bilateral(){

    bilateralFilter(poza, pozaBilaterala, ui->DiametruVecinatate->value(), ui->Culoare->value(), ui->Spatiu->value());

    cvtColor(pozaBilaterala, pozaBilaterala, COLOR_BGR2RGB);
    QImage img = QImage((uchar*) pozaBilaterala.data, pozaBilaterala.cols, pozaBilaterala.rows, pozaBilaterala.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_DiametruVecinatate_actionTriggered(int action)
{
    ui->minDiametru->setNum(ui->DiametruVecinatate->value());
    bilateral();
}

void MainWindow::on_Spatiu_actionTriggered(int action)
{
    ui->minSpatiu->setNum(ui->Spatiu->value());
    bilateral();
}

void MainWindow::on_Save_clicked()
{
    String saveName = path;
    saveName.insert(saveName.size() - 4, "Test");
    cvtColor(pozaBilaterala, pozaBilaterala, COLOR_RGB2BGR);
    imwrite(saveName, pozaBilaterala);
}

void MainWindow::on_Culoare_actionTriggered(int action)
{
    ui->minCuloare->setNum(ui->Culoare->value());
    bilateral();
}
