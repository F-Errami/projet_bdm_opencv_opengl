#ifndef NAMEDIALOG_H
#define NAMEDIALOG_H


#include"gameWindow.h"

#include <QDialog>

namespace Ui {
class NameDialog;
}

class NameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NameDialog(QWidget *parent = nullptr);
    ~NameDialog();

private slots:
    void on_enterButton_clicked();

private:
    Ui::NameDialog *ui;
};

#endif // NAMEDIALOG_H
