
#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QOpenGLWidget> // Include the QOpenGLWidget header

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



class GlWidget : public QOpenGLWidget // Inherit from QOpenGLWidget
{
    Q_OBJECT

public:
    explicit GlWidget(QWidget *parent = 0);
    ~GlWidget();

protected:
    void initializeGL() override; // Override the initializeGL function
    void paintGL() override;      // Override the paintGL function
    void resizeGL(int width, int height) override;

private:
    VideoCapture * webCam_;
    vector<Point> points;

    void CameraProcessing(mutex &m);
    void DetectionProcessing(mutex &m);

    String modelTxt = "../../../../TestWebCamQt/pose_deploy.prototxt";
    String modelBin = "../../../../TestWebCamQt/pose_iter_102000.caffemodel";
    String imageFile = "TestWebCamQt/testOpenCV/hand.jpg";
    String dataset = "HAND";

    int W_in = 368;
    int H_in = 368;
    float thresh = 0.1;
    float scale = 0.003922;
    Mat img;
    int midx, npairs, nparts;
    QImage image;

    const int POSE_PAIRS[3][20][2] = {
        // COCO body
        { {1,2}, {1,5}, {2,3},
          {3,4}, {5,6}, {6,7},
          {1,8}, {8,9}, {9,10},
          {1,11}, {11,12}, {12,13},
          {1,0}, {0,14},
          {14,16}, {0,15}, {15,17} },
        // MPI body
        { {0,1}, {1,2}, {2,3},
          {3,4}, {1,5}, {5,6},
          {6,7}, {1,14}, {14,8}, {8,9},
          {9,10}, {14,11}, {11,12}, {12,13} },
        // hand
        { {0,1}, {1,2}, {2,3}, {3,4},
          {0,5}, {5,6}, {6,7}, {7,8},
          {0,9}, {9,10}, {10,11}, {11,12},
          {0,13}, {13,14}, {14,15}, {15,16},
          {0,17}, {17,18}, {18,19}, {19,20} }
    };

    Net net;

private slots:
//    void updateFrame();
};

#endif // GLWIDGET_H
