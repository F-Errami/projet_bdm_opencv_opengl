
#ifndef HANDCONFIG_H
#define HANDCONFIG_H




#include <vector>
#include <opencv2/opencv.hpp>
#include <QString>
#include <QWidget>


#include <QTimer>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <thread>
#include <mutex>
#include <iostream>
using namespace cv;
using namespace cv::dnn;
#include <iostream>
using namespace std;


class HandConfig
{
   public:
    HandConfig();
    std::vector<cv::Point> points;
    int detectHandConfiguration(Mat img);
    double* calculateDistances(const std::vector<cv::Point>& points);
    int W_in = 368;
    int H_in = 368;
    float thresh = 0.1;
    float scale = 0.003922;
    int midx, npairs, nparts;
    int H,W;

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

    private:
    std::vector<std::vector<int>> fingerIndices_;
    double calculateDistance(const cv::Point& p1, const cv::Point& p2);
    String modelTxt = "../../../../TestWebCamQt/pose_deploy.prototxt";
    String modelBin = "../../../../TestWebCamQt/pose_iter_102000.caffemodel";
    String imageFile = "TestWebCamQt/testOpenCV/hand.jpg";
    String dataset = "HAND";



    Net net;
};


#endif // HANDCONFIG_H
