#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include "wifibot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnConnexion_clicked();

    void on_btnStop_clicked();

    void on_verticalSlider_valueChanged(int value);

    void on_btnLeft_clicked();

    void on_btnTop_clicked();

    void on_btnRight_clicked();

    void on_btnDown_clicked();

    void on_btnTopCamera_clicked();

    void on_btnRightCamera_clicked();

    void on_btnDownCamera_clicked();

    void on_btnLeftCamera_clicked();

    void on_btnUpdate_clicked();

private:
    Ui::MainWindow *ui;
    Wifibot wifibot;
};
#endif // MAINWINDOW_H
