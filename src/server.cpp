#include <QtNetwork>
#include "server.h"
#include "connection.h"
#include "client.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    listen(QHostAddress::Any, 45454);
    qDebug() << "[CONSTRUCTOR]Server started at port: " << this->serverPort();
}

void Server::incomingConnection(qintptr handle) //for establishing initial connection
{
    Connection *connection = new Connection(handle, this);
    qDebug() << "[SERVER]incomingConnection connection invoked" << endl;
    emit NewConnection(connection);
}
