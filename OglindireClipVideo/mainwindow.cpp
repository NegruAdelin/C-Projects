#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Oglindit->setEnabled(false);
    ui->Vertical->setEnabled(false);
    ui->Orizontal->setEnabled(false);
    video.open("C:/Users/negru/OneDrive/Desktop/movie.avi");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Play_clicked()
{
    Mat frame;

    if(!video.isOpened()){
        std::cout<<"Fisierul nu poate fi deschis";
    }
    else{

        ui->Oglindit->setEnabled(true);
        ui->Vertical->setEnabled(true);
        ui->Orizontal->setEnabled(true);

        namedWindow("Video");

        while(!exit && play){

            if(!video.read(frame)){
                std::cout << "Nu se poate citi fisierul video";
                break;
            }
            else{
                if(flipChose.size()){
                    for(int i = 0; i < flipChose.size(); i++){
                        flip(frame, frame, flipChose[i]);
                    }
                }

                imshow("Video", frame);

                if(waitKey(30) == 27){
                    break;
                }
            }
        }
    }
}

void MainWindow::on_Orizontal_clicked()
{
    if(std::find(flipChose.begin(), flipChose.end(), 0) != flipChose.end()){
        flipChose.erase(std::find(flipChose.begin(), flipChose.end(), 0));
    }
    else{
        flipChose.push_back(0);
    }
}

void MainWindow::on_Vertical_clicked()
{
    if(std::find(flipChose.begin(), flipChose.end(), -1) != flipChose.end()){
        flipChose.erase(std::find(flipChose.begin(), flipChose.end(), -1));
    }
    else{
        flipChose.push_back(-1);
    }
}

void MainWindow::on_Oglindit_clicked()
{
    if(std::find(flipChose.begin(), flipChose.end(), 1) != flipChose.end()){
        flipChose.erase(std::find(flipChose.begin(), flipChose.end(), 1));
    }
    else{
        flipChose.push_back(1);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(exit)
        close();
    else{
        exit = true;
        destroyAllWindows();
    }
}

void MainWindow::on_StopPlay_clicked()
{
    play = !play;
    MainWindow::on_Play_clicked();
}
