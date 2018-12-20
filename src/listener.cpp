#include "listener.h"

Listener::Listener(QObject *parent) : QTcpServer (parent)
{
    listen(QHostAddress::Any);
}

void Listener::incomingConnection(qintptr handle)
{
    //TODO
}
