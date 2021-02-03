#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Play_clicked();

    void on_Orizontal_clicked();

    void on_Vertical_clicked();

    void on_Oglindit_clicked();

    void on_pushButton_clicked();

    void on_StopPlay_clicked();

private:
    Ui::MainWindow *ui;
    std::vector<int> flipChose;
    bool play = true;
    bool exit = false;
    VideoCapture video;
};
#endif // MAINWINDOW_H
