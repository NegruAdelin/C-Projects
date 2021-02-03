#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <QColor>
#include <QColorDialog>
#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "ColorDetector.h"

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
    void on_IncarcaPoza_clicked();

    void on_Culori_clicked();

    void on_Toleranta_actionTriggered(int action);

    void on_Salveaza_clicked();

private:
    Ui::MainWindow *ui;
    ColorDetector cdetector;
    Mat poza, auxPoza;
    String adresaPozei;
    QColor culoare1, culoare2;
};
#endif // MAINWINDOW_H
