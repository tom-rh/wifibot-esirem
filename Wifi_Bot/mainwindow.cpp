#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    wifibot.moveForward();

}

void MainWindow::on_pushButton_clicked()
{
    wifibot.setSpeed(0);
    wifibot.disconnect();
}

