#include "wifibot.h"

Wifibot::Wifibot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    rightWheel=0;
    leftWheel=0;
    rightForward=1;
    leftForward=1;
    speed=100;
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x0;
    DataToSend[3] = 0x0;
    DataToSend[4] = 0x0;
    DataToSend[5] = 0x0;
    DataToSend[6] = 0x0;
    DataToSend[7] = 0x0;
    DataToSend[8] = 0x0;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer
}

void Wifibot::setSpeed(int _speed){
    speed=_speed;
}

void Wifibot::ResetMove() {
    rightWheel=0;
    leftWheel=0;
    rightForward=1;
    leftForward=1;
    setSpeed(0);
    DataToSend[2] = speed;
    DataToSend[3] = (speed>>8);
    DataToSend[4] = speed;
    DataToSend[5] = (speed>>8);
    pin6();
    CrcAndSend();
}

void Wifibot::moveForward() {
    rightWheel=1;
    leftWheel=1;
    rightForward=1;
    leftForward=1;
    DataToSend[2] = speed;
    DataToSend[3] = (speed>>8);
    DataToSend[4] = speed;
    DataToSend[5] = (speed>>8);
    pin6();
    CrcAndSend();
}

void Wifibot::moveBackward() {
    rightWheel=1;
    leftWheel=1;
    rightForward=0;
    leftForward=0;
    DataToSend[2] = speed;
    DataToSend[3] = (speed>>8);
    DataToSend[4] = speed;
    DataToSend[5] = (speed>>8);
    pin6();
    CrcAndSend();
}

void Wifibot::moveToRight(){
    rightWheel=1;
    leftWheel=1;
    rightForward=0;
    leftForward=1;
    DataToSend[2] = speed;
    DataToSend[3] = (speed>>8);
    DataToSend[4] = 0;
    DataToSend[5] = (0>>8);
    pin6();
    CrcAndSend();
}


void Wifibot::moveToLeft(){
    rightWheel=1;
    leftWheel=0;
    rightForward=1;
    leftForward=0;
    DataToSend[2] = 0;
    DataToSend[3] = (0>>8);
    DataToSend[4] = speed;
    DataToSend[5] = (speed>>8);
    pin6();
    CrcAndSend();
}

void Wifibot::pin6(){
    int val=0;
    if(rightWheel==1)val+=32;
    if(leftWheel==1)val+=128;
    if(rightForward==1)val+=16;
    if(leftForward==1)val+=64;
    DataToSend[6]=val;
}

void Wifibot::CrcAndSend(){
    unsigned char *dat = (unsigned char *)DataToSend.data();
    short crc = Crc16(dat+1,6);
    DataToSend[7] = (char)crc;
    DataToSend[8] = (char) (crc >>8);
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot()));
}

short Wifibot::Crc16(unsigned char *Adresse_tab, unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity = 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for (CptOctet = 0; CptOctet < Taille_max; CptOctet++)
    {
        Crc ^= *(Adresse_tab + CptOctet);
        for (CptBit = 0; CptBit <= 7; CptBit++)
        {
            Parity = Crc;
            Crc >>= 1;
            if (Parity % 2 == true)
                Crc ^= Polynome;
        }
    }
    return (Crc);
}

void Wifibot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

void Wifibot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

void Wifibot::connected() {
    qDebug() << "connected..."; // Hey server, tell me about you.
}

void Wifibot::disconnected() {
    qDebug() << "disconnected...";
}

void Wifibot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void Wifibot::readyRead() {
    qDebug() << "reading..."; // read the data from the socket
    DataReceived = socket->readAll();
    emit updateUI(DataReceived);
    qDebug() << DataReceived[0] << DataReceived[1] << DataReceived[2];
}

void Wifibot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

