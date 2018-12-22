#include <QtNetwork>

#include "transmitter.h"
#include "client.h"
#include "connection.h"
#include "mainwindow.h"

static const int broadcastInterval = 2000;
static const int broadcastPort = 45454;

Transmitter::Transmitter(Client *client) : QObject (client)
{
    this->client = client;
    serverPort = 0;

    broadcastSocket.bind(QHostAddress::Any, broadcastPort, QUdpSocket::ShareAddress |
                          QUdpSocket::ReuseAddressHint);

    connect(&broadcastSocket, SIGNAL(readyRead()), this, SLOT(readDatagram()));
    broadcastTimer.setInterval(broadcastInterval);
    connect(&broadcastTimer, SIGNAL(timeout()), this, SLOT(sendDatagram()));
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

        //TODO
    }
}

void Transmitter::sendDatagram()
{
    QByteArray datagram;

    QCborStreamWriter writer(&datagram);
    writer.startArray(2);
    writer.append(MainWindow::getMyNickname());
    writer.append(serverPort);
    writer.endArray();

    bool updateAddressesFlag = false;

    for(QHostAddress addr : broadcastAddrList)
    {
        if (broadcastSocket.writeDatagram(datagram, addr, broadcastPort) == -1)
            updateAddressesFlag = true; //getAllAddresses() can't be called inside
    }                                   //cause it would mess up the already valid addresses

    if(updateAddressesFlag)
        getAllAddresses();
}

void Transmitter::getAllAddresses()
{
    broadcastAddrList.clear();
    ipAddrList.clear();

    for(QNetworkInterface interface : QNetworkInterface::allInterfaces())
    {
        for(QNetworkAddressEntry addressStruct : interface.addressEntries())
        {
            QHostAddress broadcastAddress = addressStruct.broadcast();
            if (broadcastAddress != QHostAddress::Null && addressStruct.ip() != QHostAddress::LocalHost)
            {
                broadcastAddrList.append(broadcastAddress);
                ipAddrList.append(addressStruct.ip());
            }
        }
    }
}


