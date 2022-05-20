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
    /*qDebug() << "btnConnexion";
    ui->btnConnexion->setText("-");
    wifibot.doConnect();
<<<<<<< Updated upstream
    wifibot.moveToLeft();
=======
    wifibot.moveForward();*/
>>>>>>> Stashed changes
}
