//ERRAMI 

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

#include <QString>
#include <QTimer>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "cam.h"
#include <thread>
#include <mutex>
using namespace cv;
using namespace cv::dnn;
#include <iostream>
using namespace std;


namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QString name,QWidget *parent = 0);
    ~GameWindow();

private:
    Ui::GameWindow *ui;
    Cam* camera;
    vector<Point> points;
    int scoreValue=0;
    int h_score=0;

    int W_in = 368;
    int H_in = 368;
    float thresh = 0.1;
    float scale = 0.003922;


private slots:
   void  onDetectionMatch();
   void onLost();
    //void on_captureButton__clicked();
    void updateFrame();
   void on_startButton_clicked();

 signals:
   void stop();

};

#endif // GAMEWINDOW_H
