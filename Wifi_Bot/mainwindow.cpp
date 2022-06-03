#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->video->load(QUrl(QString("http://192.168.1.106:8080/?action=stream")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnexion_clicked()
{
    qDebug() << "btnConnexion";
    wifibot.doConnect();
    wifibot.setSpeed(20);
    wifibot.readyRead();
}


void MainWindow::on_btnStop_clicked()
{
    wifibot.ResetMove();
}


void MainWindow::on_btnRestart_clicked()
{
    wifibot.moveForward();
}


void MainWindow::on_verticalSlider_valueChanged(int value)
{
    wifibot.setSpeed(value);
}


void MainWindow::on_btnLeft_clicked()
{
    wifibot.moveToLeft();
}


void MainWindow::on_btnTop_clicked()
{
    wifibot.moveForward();
}


void MainWindow::on_btnRight_clicked()
{
    wifibot.moveToRight();
}


void MainWindow::on_btnDown_clicked()
{
    wifibot.moveBackward();
}

