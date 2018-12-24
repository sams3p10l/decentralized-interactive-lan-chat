#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QList>
#include <QByteArray>

class Client;
class Connection;

class Transmitter : public QObject
{
    Q_OBJECT

public:
    Transmitter(Client *client);
    bool isLocalHost(const QHostAddress &address);
    void startBroadcast();
    void setListenPort(int port);

signals:
    void newConnection(Connection *connection);

private:
    Client *client;
    int listenPort;
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
