#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    video.open("C:/Users/negru/OneDrive/Desktop/movie.avi");
    ui->Sobel->setEnabled(false);
    ui->ChangeMargin->setEnabled(false);
    ui->ChangeMargin->setMinimum(1);
    ui->ChangeMargin->setMaximum(255);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::convert_to_sobe(Mat& frame){

    Mat picture, vertical, orizontal, normaSobel, final;
    double sobMin, sobMax;

    frame.copyTo(picture);

    Sobel(picture, orizontal, CV_16S, 1, 0);
    Sobel(picture, vertical, CV_16S, 0, 1);
    normaSobel = abs(orizontal) + abs(vertical);
    minMaxLoc(normaSobel, &sobMin, &sobMax);

    normaSobel.convertTo(final, CV_8U, -255./sobMax, 255);
    cvtColor(final, final, COLOR_RGB2GRAY);
    threshold(final, final, ui->ChangeMargin->value(), 255, THRESH_BINARY);

    final.copyTo(frame);
}

void MainWindow::on_Sobel_clicked()
{
    sobel = !sobel;
}

void MainWindow::on_Play_clicked()
{
    Mat frame;
    QImage img;

    if(!video.isOpened()){
        std::cout<<"Fisierul nu poate fi deschis";
    }
    else{
        ui->Sobel->setEnabled(true);
        ui->ChangeMargin->setEnabled(true);
        ui->ChangeMargin->setValue(240);
        ui->minMargin->setNum(ui->ChangeMargin->value());

        while(true){

            if(!video.read(frame)){
                std::cout << "Nu se poate citi fisierul video";
                break;
            }
            else{
                cvtColor(frame, frame, COLOR_BGR2RGB);

                if(sobel){
                    convert_to_sobe(frame);
                    img = QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_Grayscale8);
                }
                else
                {
                    img = QImage((uchar*) frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
                }
                ui->label->setPixmap(QPixmap::fromImage(img));
                ui->label->resize(ui->label->pixmap()->size());

                waitKey(40);
            }
        }
    }
}

void MainWindow::on_ChangeMargin_actionTriggered(int action)
{
    ui->minMargin->setNum(ui->ChangeMargin->value());

}
