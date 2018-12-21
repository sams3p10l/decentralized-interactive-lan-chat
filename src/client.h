#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include <QHash>
#include <QHostAddress>

class Transmitter;

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

private:
    Transmitter *transmitter;
    Server server;
    QMultiHash<QHostAddress, Connection*> peers;

};

#endif // CLIENT_H
