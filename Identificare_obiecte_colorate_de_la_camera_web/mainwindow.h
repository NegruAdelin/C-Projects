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
#include <string>
#include <vector>
#include <QCheckBox>

using namespace cv;
using namespace std;

#define PORTOCALIU_MIN Scalar(5, 50, 50)
#define PORTOCALIU_MAX Scalar(22, 255, 255)
#define GALBEN_MIN Scalar(22, 50, 50)
#define GALBEN_MAX Scalar(38, 255, 255)
#define VERDE_MIN Scalar(38, 50, 50)
#define VERDE_MAX Scalar(75, 255, 255)
#define ALBASTRU_MIN Scalar(75, 50, 50)
#define ALBASTRU_MAX Scalar(130, 255, 255)
#define VIOLET_MIN Scalar(130, 50, 50)
#define VIOLET_MAX Scalar(160, 255, 255)
#define ROSU_MIN Scalar(160, 50, 50)
#define ROSU_MAX Scalar(179, 255, 255)
#define SATURATIE_MIN 0
#define SATURATIE_MAX 255
#define VALOARE_MIN 0
#define VALOARE_MAX 255
#define HUE_MIN 0
#define HUE_MAX 179
#define OPENED 1

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

    void detectare();

    void changeEnableCheckBTN(bool val);

    void checkAndChangeEnableCheckBTN();

    void on_VideoBTN_clicked();

    void on_PortocaliuBTN_stateChanged(int arg1);

    void on_GalbenBTN_stateChanged(int arg1);

    void on_VerdeBTN_stateChanged(int arg1);

    void on_AlbastruBTN_stateChanged(int arg1);

    void on_VioletBTN_stateChanged(int arg1);

    void on_RosuBTN_stateChanged(int arg1);

    void cautaContururi(Mat frame, Mat imgLines);

    void createThreshold(Mat frameHSV, Mat& imgThreshold);

    void setBlVar();

    void addRectangle(Mat farme, Mat imgThreshold, Mat imgLines);

private:
    Ui::MainWindow *ui;
    Mat Poza, PozaThresholded;
    int count = 0;
    bool portocaliuBL = false, galbenBL = false, rosuBL = false, verdeBL = false, albastruBL = false, violetBL = false;
};
#endif // MAINWINDOW_H
