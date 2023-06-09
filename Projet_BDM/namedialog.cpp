#include "namedialog.h"
#include "ui_namedialog.h"

NameDialog::NameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NameDialog)
{
    ui->setupUi(this);
     setFixedSize(800, 600);
}

NameDialog::~NameDialog()
{
    delete ui;
}

void NameDialog::on_enterButton_clicked()
{
    QString name = ui->entryname->text();
    // Create an instance of the GameWidget and pass the captured name
    GameWindow *gameWidget = new GameWindow(name);
    gameWidget->show();


    // Hide the StartWidget
    hide();
}

