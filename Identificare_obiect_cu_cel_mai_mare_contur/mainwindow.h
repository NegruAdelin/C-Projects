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

#define OPENED 1
using namespace cv;
using namespace std;

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
    void on_Video_clicked();

    void on_hSlider_actionTriggered(int action);

    void on_sSlider_actionTriggered(int action);

    void on_vSlider_actionTriggered(int action);

    void cautaContururi(Mat frame, Mat imgLines);

    void addRectangle(Mat farme, Mat imgThreshold, Mat imgLines);

    void on_maxHSlider_actionTriggered(int action);

    void on_maxSSlider_actionTriggered(int action);

    void on_maxVSlider_actionTriggered(int action);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
