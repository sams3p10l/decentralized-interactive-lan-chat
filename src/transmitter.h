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
    bool IsLocalHost(const QHostAddress &address);
    void SetListenPort(int port);
    QString GetUsername() const;
    void StartBroadcast();
    static void TransSetNickname(const QString &Nickname);

signals:
    void NewConnection(Connection *connection);

private:
    Client *client;
    int ListenPort;
    QUdpSocket BroadcastSocket;
    QTimer BroadcastTimer;
    static QString Nickname;
    QList<QHostAddress> BroadcastAddrList; //for sending and receiving datagrams
    QList<QHostAddress> IpAddrList; //for localhost check

    void GetAllAddresses();

private slots:
    void ReadDatagram();
    void SendDatagram();

};

#endif // TRANSMITTER_H
