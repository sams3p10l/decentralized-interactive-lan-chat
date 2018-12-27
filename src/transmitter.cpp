#include <QtNetwork>

#include "transmitter.h"
#include "client.h"
#include "connection.h"
#include "mainwindow.h"

static const int broadcastInterval = 5000;
static const unsigned broadcastPort = 45454;
QString Transmitter::nickname = "";

Transmitter::Transmitter(Client *client, QString myNick) : QObject (client)
{
    this->client = client;
    nickname = myNick;

    if (nickname.isEmpty())
        nickname = "unknown";

    getAllAddresses();
    listenPort = 0;

    broadcastSocket.bind(QHostAddress::Any, broadcastPort, QUdpSocket::ShareAddress |
                          QUdpSocket::ReuseAddressHint);

    connect(&broadcastSocket, SIGNAL(readyRead()), this, SLOT(readDatagram())); //for establishing connection
    broadcastTimer.setInterval(broadcastInterval);
    connect(&broadcastTimer, SIGNAL(timeout()), this, SLOT(sendDatagram())); //for broadcasting writer
}

void Transmitter::transSetNickname(const QString &pNickname)
{
    nickname = pNickname;
}

void Transmitter::readDatagram()
{
    while(broadcastSocket.hasPendingDatagrams())
    {
        QHostAddress senderIP;
        quint16 senderClientPort;
        QByteArray datagram;
        //QString result;

        datagram.resize(broadcastSocket.pendingDatagramSize());
        if (broadcastSocket.readDatagram(datagram.data(), datagram.size(),
                                         &senderIP, &senderClientPort) == -1)
               continue;

        int senderServerPort;
        QString username;
        QCborStreamReader reader(datagram);

        reader.enterContainer();

        while (reader.readString().status == QCborStreamReader::Ok)
        {
          //reading data into reader
        }

        senderServerPort = reader.toInteger();

        if(isLocalHost(senderIP) && senderServerPort == listenPort)
            continue;

        if(!client->clientHasConnectionCheck(senderIP, senderServerPort))
        {
            Connection *connection = new Connection(this);
            qDebug() << "[TRANSMITTER]readDatagram connection invoked " << endl;
            emit newConnection(connection);
            connection->connectToHost(senderIP, senderServerPort);
        }
    }
}

void Transmitter::sendDatagram()
{
    QByteArray datagram;
    //qDebug() << "[sendDatagram] invoked" << endl;

    QCborStreamWriter writer(&datagram);
    writer.startArray(2);
    writer.append(nickname);
    writer.append(listenPort);
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

bool Transmitter::isLocalHost(const QHostAddress &address)
{
    for(QHostAddress local : ipAddrList)
    {
        if(address.isEqual(local))
            return true;
    }
    return false;
}

void Transmitter::startBroadcast()
{
    broadcastTimer.start();
    qDebug() << "[startBroadcast] invoked" << endl;
}

void Transmitter::setListenPort(int port)
{
    listenPort = port;
}

QString Transmitter::getUsername() const
{
    return nickname;
}


