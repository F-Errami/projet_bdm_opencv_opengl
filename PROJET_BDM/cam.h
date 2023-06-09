#ifndef CAM_H
#define CAM_H
#include <QWidget>

#include <QString>
#include <QTimer>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "handconfig.h"

#include <thread>
#include <mutex>
using namespace cv;
using namespace cv::dnn;
#include <iostream>
using namespace std;

#include <QLabel>

class Cam : public QLabel
{
public:
    Cam(QWidget *parent);
    Mat getImg();
    int detectConfig();

private:
       HandConfig* handConfig;
       VideoCapture * webCam_;
       Mat img;
       bool detectionStarted= false;

private slots:
    //void on_captureButton__clicked();
    void updateFrame();

public slots:
    void stopDetection();
    void startDetection();
};


#endif // CAM_H
