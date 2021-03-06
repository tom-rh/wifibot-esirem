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
    wifibot.doConnect();
    wifibot.readyRead();
}


void MainWindow::on_btnStop_clicked()
{
    wifibot.ResetMove();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    wifibot.setSpeed(value);
}


void MainWindow::on_btnLeft_clicked()
{
    wifibot.moveToLeft();
    this->on_btnUpdate_clicked();
}


void MainWindow::on_btnTop_clicked()
{
    wifibot.moveForward();
    this->on_btnUpdate_clicked();
}


void MainWindow::on_btnRight_clicked()
{
    wifibot.moveToRight();
    this->on_btnUpdate_clicked();
}


void MainWindow::on_btnDown_clicked()
{
    wifibot.moveBackward();
    this->on_btnUpdate_clicked();
}


void MainWindow::on_btnTopCamera_clicked()
{
    wifibot.moveCamToUp();
    this->on_btnUpdate_clicked();
}


void MainWindow::on_btnRightCamera_clicked()
{
    wifibot.moveCamToRight();
    this->on_btnUpdate_clicked();
}


void MainWindow::on_btnDownCamera_clicked()
{
    wifibot.moveCamToDown();
    this->on_btnUpdate_clicked();
}


void MainWindow::on_btnLeftCamera_clicked()
{
    wifibot.moveCamToLeft();
    this->on_btnUpdate_clicked();
}

void MainWindow::on_btnUpdate_clicked()
{
    ui->batteryBar->setValue(wifibot.getBattery());
    ui->lcdSpeed->display(wifibot.getSpeed());
    ui->lcdIRD1->display(wifibot.getRightFrontIR());
    ui->lcdIRD2->display(wifibot.getRightBackIR());
    ui->lcdIRG1->display(wifibot.getLeftFrontIR());
    ui->lcdIRG2->display(wifibot.getLeftBackIR());
    ui->lcdOdometrieG->display((int)wifibot.getOdometryL());
    ui->lcdOdometrieD->display((int)wifibot.getOdometryR());
}

