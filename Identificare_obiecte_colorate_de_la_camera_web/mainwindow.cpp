#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->VideoBTN->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBlVar(){
    if(ui->PortocaliuBTN->isChecked()){
        portocaliuBL = true;
    }

    if(ui->GalbenBTN->isChecked()){
        galbenBL = true;
    }

    if(ui->VerdeBTN->isChecked()){
        verdeBL = true;
    }

    if(ui->AlbastruBTN->isChecked()){
        albastruBL = true;
    }

    if(ui->VioletBTN->isChecked()){
        violetBL = true;
    }

    if(ui->RosuBTN->isChecked()){
        rosuBL = true;
    }
}

void MainWindow::createThreshold(Mat frameHSV, Mat& imgThreshold){
    if(ui->AlbastruBTN->isChecked() && albastruBL){
        inRange(frameHSV, ALBASTRU_MIN, ALBASTRU_MAX,imgThreshold);
        albastruBL = false;

    }else if(ui->PortocaliuBTN->isChecked() && portocaliuBL){
        inRange(frameHSV, PORTOCALIU_MIN, PORTOCALIU_MAX, imgThreshold);
        portocaliuBL = false;

    }else if(ui->GalbenBTN->isChecked() && galbenBL){
        inRange(frameHSV, GALBEN_MIN, GALBEN_MAX, imgThreshold);
        galbenBL = false;

    }else if(ui->VerdeBTN->isChecked() && verdeBL){
        inRange(frameHSV, VERDE_MIN, VERDE_MAX, imgThreshold);
        verdeBL = false;

    }else if(ui->VioletBTN->isChecked() && violetBL){
        inRange(frameHSV, VIOLET_MIN, VIOLET_MAX, imgThreshold);
        violetBL = false;

    }else if(ui->RosuBTN->isChecked() && rosuBL){
       inRange(frameHSV, ROSU_MIN, ROSU_MAX, imgThreshold);
       rosuBL = false;
    }
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

        Rect boundRect = boundingRect(contours[k]);

        if(!boundRect.empty())
            rectangle(imgLines, boundRect.tl(), boundRect.br(), ROSU_MIN, 3);
    }

    frame = frame + imgLines;
    imshow("camera", frame);
}

void MainWindow::cautaContururi(Mat frame, Mat imgLines){
    Mat imgHSV, imgThreshold1, imgThreshold2;
    imgLines = Mat::zeros(frame.size(), CV_8UC3);

    cvtColor(frame, imgHSV, COLOR_BGR2HSV);
    createThreshold(imgHSV, imgThreshold1);
    createThreshold(imgHSV, imgThreshold2);

    erode(imgThreshold1, imgThreshold1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThreshold1, imgThreshold1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    dilate(imgThreshold1, imgThreshold1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThreshold1, imgThreshold1, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    erode(imgThreshold2, imgThreshold2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    dilate(imgThreshold2, imgThreshold2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    dilate(imgThreshold2, imgThreshold2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
    erode(imgThreshold2, imgThreshold2, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

    addRectangle(frame, imgThreshold1, imgLines);
    addRectangle(frame, imgThreshold2, imgLines);
    setBlVar();
}

void MainWindow::changeEnableCheckBTN(bool val){
    ui->PortocaliuBTN->setEnabled(val);
    ui->GalbenBTN->setEnabled(val);
    ui->VerdeBTN->setEnabled(val);
    ui->AlbastruBTN->setEnabled(val);
    ui->VioletBTN->setEnabled(val);
    ui->RosuBTN->setEnabled(val);
}

void MainWindow::checkAndChangeEnableCheckBTN(){
    if(!ui->PortocaliuBTN->isChecked()){
        ui->PortocaliuBTN->setEnabled(false);
    }
    if(!ui->GalbenBTN->isChecked()){
        ui->GalbenBTN->setEnabled(false);
    }
    if(!ui->VerdeBTN->isChecked()){
        ui->VerdeBTN->setEnabled(false);
    }
    if(!ui->AlbastruBTN->isChecked()){
        ui->AlbastruBTN->setEnabled(false);
    }
    if(!ui->VioletBTN->isChecked()){
        ui->VioletBTN->setEnabled(false);
    }
    if(!ui->RosuBTN->isChecked()){
        ui->RosuBTN->setEnabled(false);
    }
}

void MainWindow::detectare(){
    if(count == 2){
        checkAndChangeEnableCheckBTN();
        ui->VideoBTN->setEnabled(true);
    }
    else{
        changeEnableCheckBTN(true);
        ui->VideoBTN->setEnabled(false);
        destroyAllWindows();
    }
}



void MainWindow::on_VideoBTN_clicked()
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

void MainWindow::on_PortocaliuBTN_stateChanged(int arg1)
{
    if(arg1){
        count++;
        portocaliuBL = true;
    }
    else{
        portocaliuBL = false;
        count--;
    }

    detectare();
}

void MainWindow::on_GalbenBTN_stateChanged(int arg1)
{
    if(arg1){
        count++;
        galbenBL = true;
    }
    else{
        galbenBL = false;
        count--;
    }

    detectare();
}

void MainWindow::on_VerdeBTN_stateChanged(int arg1)
{
    if(arg1){
        count++;
        verdeBL = true;
    }
    else{
        count--;
        verdeBL = false;
    }

    detectare();
}

void MainWindow::on_AlbastruBTN_stateChanged(int arg1)
{
    if(arg1){
        count++;
        albastruBL = true;
    }
    else{
        count--;
        albastruBL = false;
    }

    detectare();
}

void MainWindow::on_VioletBTN_stateChanged(int arg1)
{
    if(arg1){
        count++;
        violetBL = true;

    }
    else{
        count--;
        violetBL = false;
    }

    detectare();
}

void MainWindow::on_RosuBTN_stateChanged(int arg1)
{
    if(arg1){
        count++;
        rosuBL = true;
    }
    else{
        count--;
        rosuBL = false;
    }

    detectare();
}
