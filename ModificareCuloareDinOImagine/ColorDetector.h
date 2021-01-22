#ifndef COLORDETECTOR_H
#define COLORDETECTOR_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <QColor>

using namespace cv;

class ColorDetector{
public:
    ColorDetector(){
        this->_mDist = 200;
        this->_target[0] = this->_target[1] =this->_target[2] = 0;
    }

    ColorDetector(const Vec3b target, int mDist):_target(target), _mDist(mDist) {};

    ColorDetector(int red, int green, int blue, int mDist):_mDist(mDist){
        this->_target[0] = red;
        this->_target[1] = green;
        this->_target[2] = blue;
    }

    void setDistance(const int);

    void setTargetColor(const Vec3b);

    void setTargetColor(const int red, const int green, const int blue);

    int getDist();

    Vec3b getTarget();

    Mat process(Mat, QColor);

private:
    int _mDist;
    Vec3b _target;
    Mat _rez;
    int getDistance(const Vec3b);
};

#endif // COLORDETECTOR_H
