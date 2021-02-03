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

    void on_Verticala_clicked();

    void on_Orizontala_clicked();

    void on_Oglindire_clicked();

    void on_pushButton_clicked();

    void on_Save_clicked();

private:
    Ui::MainWindow *ui;
    Mat poza;
};
#endif // MAINWINDOW_H
