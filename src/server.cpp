#include <QtNetwork>
#include "server.h"
#include "connection.h"
#include "client.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{
    listen(QHostAddress::Any, 45454); //vrati port ovde i promeni funkciju check na staro
    qDebug() << "[CONSTRUCTOR]Server started at port: " << this->serverPort();
}

void Server::incomingConnection(qintptr handle) //for establishing initial connection
{
    Connection *connection = new Connection(handle, this);
    qDebug() << "[SERVER]incomingConnection connection invoked" << endl;
    emit newConnection(connection);
}

void Server::startListening()
{
    /*Server* server = Client::getServerInstance();

    if(server->listen(QHostAddress::Any, 45454))
        qDebug() << "[FUNCTION]Server started listening at port: " << this->serverPort();
    else {
        qDebug() << "[FUNCTION]Server listening failed" << endl;
    }*/
}
