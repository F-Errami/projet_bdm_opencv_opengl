#include "cam.h"

Cam::Cam(QWidget * parent):QLabel(parent)
{


    handConfig = new HandConfig();
    // !!!!!!!!!!! open the webcam
    webCam_ =new VideoCapture(0);
    int width= webCam_->get(CAP_PROP_FRAME_WIDTH);
    int height=webCam_->get(CAP_PROP_FRAME_HEIGHT);

    if(!webCam_->isOpened())  // check if we succeeded
    {
      qDebug()<<"Error openning the default camera !";
    }
    else
    {
            qDebug()<<QString("Video ok, image size is %1x%2 pixels").arg(width).arg(height);
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &Cam::updateFrame);
        timer->start(60); // call updateFrame() every 30ms
        //updateFrame();
    }



}


void Cam ::updateFrame()
{
    if (webCam_->isOpened()) {
        webCam_->read(img);
        if (img.empty())
        {
            std::cerr << "Cannot read frame from webcam" << std::endl;

        }
    Mat img_sk= img;

    if(detectionStarted)
    {
    // connect body parts and draw it !
           float SX = float(img.cols) / handConfig->W;
           float SY = float(img.rows) / handConfig->H;
           for (int n=0; n<handConfig->npairs; n++)
           {
               // lookup 2 connected body/hand parts
               Point2f a = handConfig->points[handConfig->POSE_PAIRS[handConfig->midx][n][0]];
               Point2f b = handConfig->points[handConfig->POSE_PAIRS[handConfig->midx][n][1]];
               // we did not find enough confidence before
               if (a.x<=0 || a.y<=0 || b.x<=0 || b.y<=0)
                   continue;
               // scale to image size
               a.x*=SX; a.y*=SY;
               b.x*=SX; b.y*=SY;
               line(img_sk, a, b, Scalar(0,200,0), 2);
               circle(img_sk, a, 3, Scalar(0,0,200), -1);
               circle(img_sk, b, 3, Scalar(0,0,200), -1);
           }

    }


    // Convert to Qt image
    QImage image = QImage((const unsigned char*)(img_sk.data), img_sk.cols, img_sk.rows, QImage::Format_RGB888);

    // Create a pixmap from the image
    QPixmap pixmap = QPixmap::fromImage(image);

    // Calculate the desired smaller size for the label
    int smallerWidth = pixmap.width() / 5;  // adjust the division factor as needed
    int smallerHeight = pixmap.height() / 5;  // adjust the division factor as needed

    // Resize the pixmap to the smaller size
    QPixmap smallerPixmap = pixmap.scaled(smallerWidth, smallerHeight, Qt::KeepAspectRatio);

    // Display the smaller pixmap on the label
    this->setPixmap(smallerPixmap);

    // Resize the label to fit the smaller pixmap
    this->setFixedSize(smallerPixmap.size());

}

}


int Cam ::detectConfig()
{

    return handConfig->detectHandConfiguration(img);
}

Mat Cam ::getImg()
{
    return img;
}

void Cam ::startDetection()
{
    detectionStarted= true;
}

void Cam ::stopDetection()
{
    detectionStarted= false;
}





