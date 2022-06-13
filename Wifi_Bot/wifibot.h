#ifndef WIFIBOT_H
#define WIFIBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QNetworkAccessManager>

class Wifibot : public QObject {
    Q_OBJECT
public:
    explicit Wifibot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    void setSpeed(int _speed);
    void ResetMove();
    void moveForward();
    void moveBackward();
    void moveToRight();
    void moveToLeft();
    void moveCamToLeft();
    void moveCamToRight();
    void moveCamToUp();
    void moveCamToDown();
    void pin6();
    void CrcAndSend();
    short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);
    int getSpeed();
    int getBattery();
    int getIR();
    int getIR2();
    long getOdometryL();
    long getOdometryR();

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
    int speed;
    bool rightWheel;
    bool leftWheel;
    bool rightForward; //1-->forward, 0-->backward
    bool leftForward; //1-->forward, 0-->backward
    //
    int etat; //0-->forward, 1-->
    int levelBattery;
    int currentSpeed;
    int IR, IR2;
    long currentOdometryR, currentOdometryL, odometryR, odometryL, odometryROr, odometryLOr;
    int odometryTest;
    QNetworkAccessManager *Camera;
};

#endif // WIFIBOT_H
