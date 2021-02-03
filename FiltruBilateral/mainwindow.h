#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <string>
#include <stdlib.h>

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
    void on_ChooseFile_clicked();

    void bilateral();

    void on_DiametruVecinatate_actionTriggered(int action);

    void on_Spatiu_actionTriggered(int action);

    void on_Save_clicked();

    void on_Culoare_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    Mat poza, pozaBilaterala;
    String path;
};
#endif // MAINWINDOW_H
