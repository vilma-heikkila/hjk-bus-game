#include "dialog.hh"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->pulsu1Button->setChecked(true);
    pulsuType_ = 1;


    QImage img;
    img.load(":/data/data/pulsu1.png");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0,0,208,298);       // image dimensions

    scene->setBackgroundBrush(img);
    Dialog::setWindowTitle("Pulsupeli");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pulsu1Button_clicked()
{
    QImage img;
    img.load(":/data/data/pulsu1.png");
    scene->setSceneRect(0,0,208,298);       // pulsu1.png dimensions
    scene->setBackgroundBrush(img);

    pulsuType_ = 1;
    twoPlayerMode_ = false;
}

void Dialog::on_pulsu2Button_clicked()
{
    QImage img;
    img.load(":/data/data/pulsu2.png");     // pulsu2.png dimensions
    scene->setSceneRect(0,0,208,298);
    scene->setBackgroundBrush(img);

    pulsuType_ = 2;
    twoPlayerMode_ = false;
}

void Dialog::accept()
{
    sendPulsuType(pulsuType_);
    sendTwoPlayerMode(twoPlayerMode_);
    QDialog::accept();
}

void Dialog::reject()
{
    emit dontStart();
    QDialog::reject();
}

void Dialog::on_twoPlayerButton_clicked()
{
    pulsuType_ = 1;
    twoPlayerMode_ = true;
}
