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
    void on_Sobel_clicked();

    void on_Play_clicked();

    void convert_to_sobe(Mat& frame);

    void on_ChangeMargin_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    std::vector<int> flipChose;
    bool sobel = false;
    bool exit = false;
    VideoCapture video;
};
#endif // MAINWINDOW_H
