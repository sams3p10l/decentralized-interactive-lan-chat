#ifndef TRANSMITTER_H
#define TRANSMITTER_H

#include <QObject>
#include <QUdpSocket>

class Client;

class Transmitter : public QObject
{
    Q_OBJECT

public:
    Transmitter(Client *client);

private:
    Client *client;
    int serverPort;
    QUdpSocket broadcastSocket;

private slots:
    void readDatagram();

};

#endif // TRANSMITTER_H
