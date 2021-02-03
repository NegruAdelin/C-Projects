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
    void on_Image_clicked();

    void set_height_width(Mat picture);

    void filtru(Mat picture);

    void on_Save_clicked();

    void on_Culoare_sliderReleased();

    void on_Diametru_sliderReleased();

    void on_Spatiu_sliderReleased();

    void on_threshold1_sliderReleased();

    void on_threshold2_sliderReleased();

    void on_threshold1_actionTriggered(int action);

    void on_threshold2_actionTriggered(int action);

    void on_Diametru_actionTriggered(int action);

    void on_Culoare_actionTriggered(int action);

    void on_Spatiu_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
    Mat poza, canny, aux, saveCanny, saveFiltru;
    int h, w;
    bool on = false;
};
#endif // MAINWINDOW_H
