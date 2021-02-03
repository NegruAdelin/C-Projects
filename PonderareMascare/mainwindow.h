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
    void on_poza_clicked();

    void set_height_width(Mat picture);

    void pondre_binara(Mat picture);

    void on_dstSlider_actionTriggered(int action);

    void on_thresholdSlider_actionTriggered(int action);

    void on_Save_clicked();

private:
    Ui::MainWindow *ui;
    Mat poza, poza_binara, poza_combinata;
    int h, w;
    bool on = false;
};
#endif // MAINWINDOW_H
