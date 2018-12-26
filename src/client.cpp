#include <QtNetwork>

#include "client.h"
#include "transmitter.h"
#include "connection.h"

Client::Client()
{
    transmitter = new Transmitter(this);

    transmitter->setListenPort(server.serverPort());

    QObject::connect(transmitter, SIGNAL(newConnection(Connection*)), this,
                     SLOT(newConnection(Connection*)));
    QObject::connect(&server, SIGNAL(newConnection(Connection*)), this,
                     SLOT(newConnection(Connection*)));
    QObject::connect(this, SIGNAL(startListening()), &server, SLOT(startListening()));

}

void Client::transmitterStartBroadcast()
{
    transmitter->startBroadcast();
}

void Client::startListeningSlot()
{
    emit startListening();
}

void Client::sendMessage(const QString &message)
{
    if(message.isEmpty())
        return;

    QList<Connection *> connections = peers.values();

    for(Connection *connection : connections)
        connection->sendMessage(message);
}

void Client::newConnection(Connection *connection) //deduce connection state
{
    connection->setGreetingMsg(transmitter->getUsername());

    connect(connection, SIGNAL(connectionReady()), this, SLOT(connectionReady()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnected()));
}

void Client::connectionReady()
{
    Connection *connection = qobject_cast<Connection *>(sender()); //returns a pointer to object that sent a signal
                                                                   //in this case our successful connection
    if(clientHasConnectionCheck(connection->peerAddress(), connection->peerPort()))
        return;

    connect(connection, SIGNAL(newMessage(QString, QString)), this, SIGNAL(newMessage()));

    peers.insert(connection->peerAddress(), connection);

    QString nick = connection->getIncomingConnectionUsername();
    if (!nick.isEmpty())
        emit newParticipant(nick);
}

bool Client::clientHasConnectionCheck(const QHostAddress &senderIP, int senderPort) const
{
    if(senderPort == -1 || !peers.contains(senderIP))
        return false;

    QList<Connection *> connections = peers.values(senderIP);

    for(Connection *connection : connections)
    {
        if(connection->peerPort() == senderPort)
            return true;
    }

    return false;
}

void Client::disconnected()
{
    Connection *connection = qobject_cast<Connection *>(sender());
    removeConnection(connection);
}

void Client::removeConnection(Connection *connection)
{
    if (peers.contains(connection->peerAddress()))
    {
        peers.remove(connection->peerAddress());
        QString nick = connection->getIncomingConnectionUsername();
        if (!nick.isEmpty())
            emit participantLeft(nick);
    }

    connection->deleteLater();
}

QString Client::fullLocalNickname() const
{
    return transmitter->getUsername() + '@' + QHostInfo::localHostName()
            + ':' + QString::number(server.serverPort());
}
