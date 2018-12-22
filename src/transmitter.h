#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QList>
#include <QByteArray>

class Client;

class Transmitter : public QObject
{
    Q_OBJECT

public:
    Transmitter(Client *client);

private:
    Client *client;
    qint16 serverPort;
    QUdpSocket broadcastSocket;
    QTimer broadcastTimer;
    QString nickname;
    QList<QHostAddress> broadcastAddrList; //for sending and receiving datagrams
    QList<QHostAddress> ipAddrList; //for localhost check

    void getAllAddresses();

private slots:
    void readDatagram();
    void sendDatagram();

};

#endif // TRANSMITTER_H
