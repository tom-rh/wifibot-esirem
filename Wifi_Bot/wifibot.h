#ifndef WIFIBOT_H
#define WIFIBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>

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
    void pin6();
    void CrcAndSend();
    short Crc16(unsigned char *Adresse_tab, unsigned char Taille_max);

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
};

#endif // WIFIBOT_H
