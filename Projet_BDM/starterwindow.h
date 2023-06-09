#ifndef STARTERWINDOW_H
#define STARTERWINDOW_H

#include <QMainWindow>
#include "namedialog.h"

namespace Ui {
class StarterWindow;
}

class StarterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StarterWindow(QWidget *parent = nullptr);
    ~StarterWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::StarterWindow *ui;
};

#endif // STARTERWINDOW_H
