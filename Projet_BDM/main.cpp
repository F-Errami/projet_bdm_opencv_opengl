#include "gameWindow.h"
#include <QApplication>
#include "starterwindow.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

     StarterWindow w;
     w.show();
    return a.exec();
}


