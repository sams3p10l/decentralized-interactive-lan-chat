#include <QtNetwork>
#include "server.h"
#include "connection.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    connect(parent, SIGNAL(startListening()), this, SLOT(startListening()));
}

void Server::incomingConnection(qintptr handle)
{
    Connection *connection = new Connection(handle, this);
    emit newConnection(connection);
}

void Server::startListening()
{
    this->listen(QHostAddress::Any);
}
