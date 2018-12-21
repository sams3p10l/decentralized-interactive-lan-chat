#include "transmitter.h"
#include "client.h"

static const int broadcastInterval = 2000;
static const int broadcastPort = 45454;

Transmitter::Transmitter(Client *client) : QObject (client)
{
    this->client = client;
    serverPort = 0;

    broadcastSocket.bind(QHostAddress::Any, broadcastPort, QUdpSocket::ShareAddress |
                          QUdpSocket::ReuseAddressHint);

    connect(&broadcastSocket, SIGNAL(readyRead()), this, SLOT(readDatagram()));
}

void Transmitter::readDatagram()
{
    while(broadcastSocket.hasPendingDatagrams())
    {
        QHostAddress senderIP;
        quint16 senderPort;
        QByteArray datagram;

        datagram.resize(broadcastSocket.pendingDatagramSize());
        broadcastSocket.readDatagram(datagram.data(), datagram.size(), &senderIP, &senderPort);

    }
}
