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
    Transmitter(Client *client, QString myNick);
    bool isLocalHost(const QHostAddress &address);
    void setListenPort(int port);
    QString getUsername() const;
    void startBroadcast();
    static void transSetNickname(const QString &nickname);

signals:
    void newConnection(Connection *connection);

private:
    Client *client;
    int listenPort;
    QUdpSocket broadcastSocket;
    QTimer broadcastTimer;
    static QString nickname;
    QList<QHostAddress> broadcastAddrList; //for sending and receiving datagrams
    QList<QHostAddress> ipAddrList; //for localhost check

    void getAllAddresses();

private slots:
    void readDatagram();
    void sendDatagram();

};

#endif // TRANSMITTER_H
