#include "gameWindow.h"
#include <QDebug>
#include <QDir>
#include "ui_gameWindow.h"
#include <QMessageBox>

#include <QString>
#include <QTimer>
#include <opencv2/dnn.hpp>
#include <unistd.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <QScreen>
#include <cstdlib>
using namespace cv;
using namespace cv::dnn;
#include <iostream>
using namespace std;

GameWindow::GameWindow(QString name,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{


    //main widget properties
    ui->setupUi(this);
    ui->username->setText(QString::fromStdString("Username :") + name);
    // Set the desired size
    setFixedSize(800, 600);
    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);
    ui->giveupButton->hide();
/////////////////////////////////////////
    ui->openGLWidget->setCam(ui->imageLabel_);
    connect(ui->openGLWidget,&MyGLWidget::loss,this,&GameWindow::onLost);
    connect(ui->openGLWidget,&MyGLWidget::loss,ui->imageLabel_,&Cam::stopDetection);
    connect(ui->openGLWidget,&MyGLWidget::match,this,&GameWindow::onDetectionMatch);
    connect(ui->openGLWidget,&MyGLWidget::near ,ui->imageLabel_,&Cam::startDetection);
    connect(ui->openGLWidget,&MyGLWidget::far,ui->imageLabel_,&Cam::stopDetection);
    connect(ui->startButton,&QPushButton::clicked,ui->openGLWidget,&MyGLWidget::replay);
    connect(ui->giveupButton,&QPushButton::clicked,this,&GameWindow::onLost);
    connect(this, &GameWindow::stop,ui->openGLWidget,&MyGLWidget::stopGame);



}


GameWindow::~GameWindow()
{
    delete ui;
    delete camera;
}

void GameWindow::updateFrame()
{






}
void GameWindow::onLost()
{
    emit stop();
    ui->status->setText("Status : Loser");

    QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::NoIcon);
      msgBox.setText(QString("Game over. your score is %1").arg(scoreValue));
      msgBox.exec();
      ui->match->setText("");
      scoreValue =0;
      ui->score->setText(QString("score: %1").arg(scoreValue));

}

void GameWindow::onDetectionMatch()
{
    scoreValue++;
    ui->score->setText(QString("score: %1").arg(scoreValue));
    ui->match->setText("Match +1");

    if(h_score<scoreValue)
    {
        h_score= scoreValue;
    }

       ui->h_score->setText(QString("High score: %1").arg(h_score));


}

void GameWindow::on_startButton_clicked()
{
    ui->giveupButton->show();
    scoreValue =0;
    ui->score->setText(QString("score: %1").arg(scoreValue));
    ui->openGLWidget->startGame();
    ui->startButton->setText("Restart");
    ui->status->setText("Status : Unknown");
}



