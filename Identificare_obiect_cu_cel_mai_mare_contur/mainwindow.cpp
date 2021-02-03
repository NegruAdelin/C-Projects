#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->minHue->setNum(0);
    ui->minValue->setNum(0);
    ui->minSaturation->setNum(0);

    ui->minHue2->setNum(0);
    ui->minValue2->setNum(0);
    ui->minSaturation2->setNum(0);

    ui->sSlider->setMinimum(0);
    ui->sSlider->setMaximum(255);
    ui->vSlider->setMinimum(0);
    ui->vSlider->setMaximum(255);
    ui->hSlider->setMinimum(0);
    ui->hSlider->setMaximum(179);
    ui->maxSSlider->setMinimum(0);
    ui->maxSSlider->setMaximum(255);
    ui->maxVSlider->setMinimum(0);
    ui->maxVSlider->setMaximum(255);
    ui->maxHSlider->setMinimum(0);
    ui->maxHSlider->setMaximum(179);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addRectangle(Mat frame,Mat imgThreshold, Mat imgLines){
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(imgThreshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0,0));

    if(contours.size() > 0){
        vector<Point2f> center(contours.size());
        vector<float> radius(contours.size());
        size_t k = -1;
        double razaMax = 0;

        for(size_t i = 0; i < contours.size(); i++){
            minEnclosingCircle((Mat)contours[i], center[i], radius[i]);
            if(razaMax < radius[i]){
                razaMax = radius[i];
                k = i;
            }
        }

        drawContours(imgLines, contours, k, Scalar(255, 0 ,0), 5);
    }

    frame = frame + imgLines;
    imshow("camera", frame);
}

void MainWindow::cautaContururi(Mat frame, Mat imgLines){
    Mat imgHSV, imgThreshold;
    imgLines = Mat::zeros(frame.size(), CV_8UC3);

    cvtColor(frame, imgHSV, COLOR_BGR2HSV);
    inRange(imgHSV, Scalar(ui->hSlider->value(), ui->sSlider->value(), ui->vSlider->value()),
            Scalar(ui->maxHSlider->value(), ui->maxSSlider->value(), ui->maxVSlider->value()), imgThreshold);


    erode(imgThreshold, imgThreshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThreshold, imgThreshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    dilate(imgThreshold, imgThreshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThreshold, imgThreshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));


    addRectangle(frame, imgThreshold, imgLines);

}

void MainWindow::on_Video_clicked()
{
    VideoCapture clip(0);

    if(!clip.isOpened()){
        cout << "Camera nu functioneaza sau nu este permisa deschiderea ei\n";
    }
    else {

        Mat frame;
        clip >> frame;
        Mat imgLines;

        do{
            clip >> frame;
            cautaContururi(frame, imgLines);
            waitKey(30);
        }while(getWindowProperty("camera", OPENED) == OPENED);
    }
    clip.release();
    destroyAllWindows();
}

void MainWindow::on_hSlider_actionTriggered(int action)
{
    ui->minHue->setNum(ui->hSlider->value());
}

void MainWindow::on_sSlider_actionTriggered(int action)
{
    ui->minSaturation->setNum(ui->sSlider->value());
}

void MainWindow::on_vSlider_actionTriggered(int action)
{
    ui->minValue->setNum(ui->vSlider->value());
}

void MainWindow::on_maxHSlider_actionTriggered(int action)
{
    ui->minHue2->setNum(ui->maxHSlider->value());
}

void MainWindow::on_maxSSlider_actionTriggered(int action)
{
    ui->minSaturation2->setNum(ui->maxSSlider->value());
}

void MainWindow::on_maxVSlider_actionTriggered(int action)
{
     ui->minValue2->setNum(ui->maxVSlider->value());
}
