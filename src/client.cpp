#include <QtNetwork>

#include "client.h"
#include "transmitter.h"
#include "connection.h"

Server *Client::server;

Client::Client()
{
    Transmitter = NicknameDialog::GetTransmitterInstance();
    server = new Server();

    QObject::connect(server, SIGNAL(NewConnection(Connection*)), this,
                     SLOT(NewConnection(Connection*)));

}

Server* Client::GetServerInstance()
{
    return server;
}

void Client::SendMessage(const QString &message)
{
    if(message.isEmpty())
        return;

    QList<Connection *> connections = Peers.values();

    for(Connection *connection : connections)
        connection->SendMessage(message);
}

void Client::NewConnection(Connection *connection) //deduce connection state
{
    connection->SetGreetingMsg(Transmitter->GetUsername());

    connect(connection, SIGNAL(connectionReady()), this, SLOT(ConnectionReady()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(Disconnected()));
}

void Client::ConnectionReady()
{
    Connection *connection = qobject_cast<Connection *>(sender()); //returns a pointer to object that sent a signal
                                                                   //in this case our successful connection
    if(ClientHasConnectionCheck(connection->peerAddress(), connection->peerPort()))
        return;

    connect(connection, SIGNAL(NewMessage(QString, QString)), this, SIGNAL(NewMessage(QString, QString)));

    Peers.insert(connection->peerAddress(), connection);

    QString nick = connection->GetIncomingConnectionUsername();
    if (!nick.isEmpty())
        emit NewParticipant(nick);
}

bool Client::ClientHasConnectionCheck(const QHostAddress &senderIP, int senderPort) const
{
    if(senderPort == -1 || !Peers.contains(senderIP))
        return false;

    QList<Connection *> connections = Peers.values(senderIP);

    for(Connection *connection : connections)
    {
        if(connection->peerPort() == senderPort)
            return true;
    }

    return false;
}

void Client::Disconnected()
{
    Connection *connection = qobject_cast<Connection *>(sender());
    RemoveConnection(connection);
}

void Client::RemoveConnection(Connection *connection)
{
    if (Peers.contains(connection->peerAddress()))
    {
        Peers.remove(connection->peerAddress());
        QString nick = connection->GetIncomingConnectionUsername();
        if (!nick.isEmpty())
            emit ParticipantLeft(nick);
    }

    connection->deleteLater();
}

QString Client::FullLocalNickname() const
{
    return Transmitter->GetUsername() + '@' + QHostInfo::localHostName()
            + ':' + QString::number(server->serverPort());
}
