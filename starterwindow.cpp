#include "starterwindow.h"
#include "ui_starterwindow.h"
#include "gameWindow.h"
#include <QSurfaceFormat>
#include "myglwidget.h"
//#include "glwidget.h"

StarterWindow::StarterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StarterWindow)
{
    ui->setupUi(this);
    // Set the desired size

    QPixmap pixmap("../../../../TestWebCamQt/img/logo.png");
    QIcon ButtonIcon(pixmap);
     ui->pushButton->setIcon(ButtonIcon);
     ui->pushButton->setIconSize(pixmap.rect().size());
     setFixedSize(800, 600);
}

StarterWindow::~StarterWindow()
{
    delete ui;
}

void StarterWindow::on_pushButton_clicked()
{
    // Close the current window
   close();

   NameDialog* w = new NameDialog();
   w->show();
}

