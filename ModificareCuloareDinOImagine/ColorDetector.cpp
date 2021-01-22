#include "ColorDetector.h"

int ColorDetector::getDistance(const Vec3b color){

    return abs(this->_target[0] - color[0]) + abs(this->_target[1] - color[1]) +
            abs(this->_target[2] - color[2]);
}

void ColorDetector::setDistance(const int dist){
    if(dist < 0)
        this->_mDist = 0;
    else
        this->_mDist = dist;
}

void ColorDetector::setTargetColor(const Vec3b color){
    this->_target = color;
}

void ColorDetector::setTargetColor(const int red, const int green, const int blue){
    this->_target[0] = red;
    this->_target[1] = green;
    this->_target[2] = blue;
}

int ColorDetector::getDist(){
    return this->_mDist;
}

Vec3b ColorDetector::getTarget(){
    return this->_target;
}

Mat ColorDetector::process(Mat image, QColor color){

    this->_rez.create(image.rows, image.cols, CV_8UC3);

    Mat_<Vec3b>::const_iterator ibegin = image.begin<Vec3b>();
    Mat_<Vec3b>::const_iterator iend = image.end<Vec3b>();
    Mat_<Vec3b>::iterator iout = this->_rez.begin<Vec3b>();

    for(;ibegin != iend; ibegin++, iout++){

        if(getDistance(*ibegin) < this->_mDist){
            (*iout)[0] = color.red();
            (*iout)[1] = color.green();
            (*iout)[2] = color.blue();
        }
        else{
            *iout = *ibegin;
        }
    }

    return this->_rez;
}
