#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    void on_btnRestart_clicked();

private:
    Ui::MainWindow *ui;
    Wifibot wifibot;
};
#endif // MAINWINDOW_H
