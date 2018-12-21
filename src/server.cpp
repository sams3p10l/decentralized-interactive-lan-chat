#include <QtNetwork>
#include "server.h"
#include "connection.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void Server::incomingConnection(qintptr handle)
{
    Connection *connection = new Connection(handle, this);
    emit newConnection(connection);
}
