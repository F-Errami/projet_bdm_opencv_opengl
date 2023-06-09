#include "glwidget.h"
#include <QPainter>

GlWidget::GlWidget(QWidget *parent) :
    QOpenGLWidget(parent)
{
}






GlWidget::~GlWidget()
{
     delete webCam_;
}

void GlWidget::initializeGL()
{
    // Initialize OpenGL settings
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    std::mutex mutx;

//    // starts the two threads
//      std:: thread th1([&]() { CameraProcessing(mutx); });
//      std::thread th2([&]() { DetectionProcessing(mutx); });

//    // wait for the end
//    th1.join();
//    th2.join();
//    // Paint OpenGL scene here

//    int x = 10;
//    int y = 10;

           // Create a QPainter and draw the image at the desired position
//    QPainter painter;
//     painter.begin(this);
//    painter.drawImage(x, y, image);


//     painter.end();
}

void GlWidget::resizeGL(int width, int height)
{
    // Handle resize event
    glViewport(0, 0, width, height);
}





void GlWidget::CameraProcessing(mutex &m)
{



        m.lock();
//        // read the network model
//        net = readNet(modelBin, modelTxt);

//        if (webCam_->isOpened()) {
//            webCam_->read(img);
//            if (img.empty())
//            {
//                std::cerr << "Cannot read frame from webcam" << std::endl;

//            }

////            // connect body parts and draw it !
////            float SX = float(img.cols) / W;
////            float SY = float(img.rows) / H;
////            for (int n=0; n<npairs; n++)
////            {
////                // lookup 2 connected body/hand parts
////                Point2f a = points[POSE_PAIRS[midx][n][0]];
////                Point2f b = points[POSE_PAIRS[midx][n][1]];
////                // we did not find enough confidence before
////                if (a.x<=0 || a.y<=0 || b.x<=0 || b.y<=0)
////                    continue;
////                // scale to image size
////                a.x*=SX; a.y*=SY;
////                b.x*=SX; b.y*=SY;
////                line(img, a, b, Scalar(0,200,0), 2);
////                circle(img, a, 3, Scalar(0,0,200), -1);
////                circle(img, b, 3, Scalar(0,0,200), -1);
//            }

//            // Convert to Qt image
//            QImage image= QImage((const unsigned char*)(img.data),img.cols,img.rows,QImage::Format_RGB888);
            // Display on label

        m.unlock();
//       this_thread::sleep_for(chrono::milliseconds(10));
    }



void GlWidget::DetectionProcessing(mutex &m)
{

        m.lock();
//        if (!img.empty()){

//        Mat inputBlob = blobFromImage(img, scale, Size(W_in, H_in), Scalar(0, 0, 0), false, false);
//        net.setInput(inputBlob);
//        Mat result = net.forward();
//        // the result is an array of "heatmaps", the probability of a body part being in location x,y
//        int H = result.size[2];
//        int W = result.size[3];
//        // find the position of the body parts
//        for (int n=0; n<nparts; n++)
//        {
//            // Slice heatmap of corresponding body's part.
//            Mat heatMap(H, W, CV_32F, result.ptr(0,n));
//            // 1 maximum per heatmap
//            Point p(-1,-1),pm;
//            double conf;
//            minMaxLoc(heatMap, 0, &conf, 0, &pm);
//            if (conf > thresh)
//                p = pm;
//            points[n] = p;
//        }

//        //ici on va determiner la configuration de la main

//        HandConfig* handconfig_= new HandConfig();
//       int config = handconfig_->detectHandConfiguration(points);
//        qDebug() << "configuration  " << config ;


//}


        m.unlock();



}

