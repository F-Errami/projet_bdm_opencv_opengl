#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "state.h"
#include <QString>
#include <QTimer>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "cam.h"
#include "handconfig.h"

#include <thread>
#include <mutex>
using namespace cv;
using namespace cv::dnn;
#include <iostream>
#include<QOpenGLTexture>
using namespace std;


// Classe dediee a l'affichage d'une scene OpenGL
class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:

    // Constructeur
    MyGLWidget(QWidget * parent = nullptr);
    void setCam(Cam *cam);



protected:


    // Fonction d'initialisation
    virtual void initializeGL() override;

    // Fonction de redimensionnement
    virtual void resizeGL(int width, int height) override;

    // Fonction d'affichage
    virtual void paintGL() override;
private :
    GLuint * m_textureId; // Texture ID
    QOpenGLTexture* walltexture; //

    void drawCube();
    void drawWall();
    void drawHand(int id);
    QTimer *timer;
    float distance;
    State *w_State;
    State *h_State;
    Cam* cam;
//    HandConfig detector;
    int randomId ;
    int detectedId;
    bool gameStarted=false;


  public slots:
    void startGame();
    void replay();
    void stopGame();


signals:
    void match();
    void loss();
    void near();
    void far();


};

#endif // MYGLWIDGET_H
