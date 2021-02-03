#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->AlegeDirector->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_AlegeDirector_clicked()
{
    int totalFiles = 0, modifiedFiles = 0;
    QString fileName =  QFileDialog::getExistingDirectory(this, tr("Alege Director"), "");
    std::string path = fileName.toStdString();
    std::vector<std::string> files;
    glob(path, files, false);


    mkdirComand = "mkdir \"" + path + "/" + dirName + "\"";
    system(mkdirComand.c_str());


    if(files.begin() != files.end()){
        for(int i = 0; i < files.size(); i++){

            poza = imread(files[i]);
            if(poza.data){
                totalFiles++;

                if(logo.rows <= poza.rows && logo.cols <= poza.cols){
                    modifiedFiles++;

                    Mat arieInteres = poza(Rect((poza.cols - logo.cols),
                                                (poza.rows - logo.rows),
                                                logo.cols, logo.rows));

                    addWeighted(arieInteres, 1, logo, 0.1, 0, arieInteres);
                    std::string fileName = files[i].substr(path.size(),
                                              files[i].size() - path.size());

                    imwrite(path + "/" + dirName + fileName, poza);
                }
            }
        }

        ui->valPoze->setNum(totalFiles);
        ui->valModificate->setNum(modifiedFiles);
    }
}

void MainWindow::on_AlegeLogo_clicked()
{
    QString fileName =  QFileDialog::getOpenFileName(this, tr("Alege Logo"), "",
                                                     tr("Image File (*.png, *.jpg)"));
     logo = imread(fileName.toLatin1().data());

     if(logo.data){
         ui->AlegeDirector->setEnabled(true);
         cvtColor(logo, logo, COLOR_BGR2RGB);
         QImage img = QImage((uchar*) logo.data, logo.cols, logo.rows, logo.step, QImage::Format_RGB888);
         ui->label->setPixmap(QPixmap::fromImage(img));
         ui->label->resize(ui->label->pixmap()->size());
     }
}
