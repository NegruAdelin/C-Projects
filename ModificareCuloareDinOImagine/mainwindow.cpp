#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Culori->setEnabled(false);
    ui->Salveaza->setEnabled(false);
    ui->Toleranta->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_IncarcaPoza_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("Alege Logo"), "",
                                                     tr("Image File (*.png, *.jpg, *.PNG, *.JPG)"));
    poza = imread(fileName.toLatin1().data());
    adresaPozei = fileName.toLatin1().data();

    if(poza.data){
        ui->Culori->setEnabled(true);
        ui->Salveaza->setEnabled(true);
        ui->valMax->setNum(255);
        ui->valMin->setNum(0);

        cvtColor(poza, poza, COLOR_BGR2RGB);
        QImage img = QImage((uchar*) poza.data, poza.cols, poza.rows, poza.step, QImage::Format_RGB888);
        ui->label->setPixmap(QPixmap::fromImage(img));
        ui->label->resize(ui->label->pixmap()->size());

    }
}

void MainWindow::on_Culori_clicked()
{
    culoare1 = QColorDialog::getColor(Qt::blue, this, "Selectati culoarea 1");
    culoare2 = QColorDialog::getColor(Qt::blue, this, "Selectati culoarea 2");

    ui->Toleranta->setEnabled(true);
    ui->Toleranta->setMinimum(0);
    ui->Toleranta->setMaximum(255);
}

void MainWindow::on_Toleranta_actionTriggered(int action)
{
    int min = ui->Toleranta->value();
    int red = culoare1.red(),
        green = culoare1.green(),
        blue = culoare1.blue();

    ui->valMin->setNum(min);

    cdetector.setDistance(min);
    cdetector.setTargetColor(red, green, blue);

    auxPoza = cdetector.process(poza, culoare2);
    QImage img = QImage((uchar*) auxPoza.data, auxPoza.cols, auxPoza.rows, auxPoza.step, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_Salveaza_clicked()
{
    adresaPozei.insert(adresaPozei.size() - 4, "Test");

    if(auxPoza.data){
        cvtColor(auxPoza, auxPoza, COLOR_BGR2RGB);
        if(imwrite(adresaPozei,auxPoza)){
            ui->text->setText("Poza a fost salvata");
            waitKey(2000);
            ui->text->setText("");
        }
        cvtColor(auxPoza, auxPoza, COLOR_BGR2RGB);
    }
    else{
        cvtColor(poza, poza, COLOR_BGR2RGB);
        if(imwrite(adresaPozei,poza)){
            ui->text->setText("Poza a fost salvata");
            waitKey(2000);
            ui->text->setText("");
        }
        cvtColor(poza, poza, COLOR_BGR2RGB);
    }
}

