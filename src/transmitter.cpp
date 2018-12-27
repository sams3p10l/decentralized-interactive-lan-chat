#include <QtNetwork>

#include "transmitter.h"
#include "client.h"
#include "connection.h"
#include "mainwindow.h"

static const int BroadcastInterval = 5000;
static const unsigned BroadcastPort = 45454;
QString Transmitter::Nickname = "";

Transmitter::Transmitter(Client *client, QString myNick) : QObject (client)
{
    this->client = client;
    Nickname = myNick;

    if (Nickname.isEmpty())
        Nickname = "unknown";

    GetAllAddresses();
    ListenPort = 0;

    BroadcastSocket.bind(QHostAddress::Any, BroadcastPort, QUdpSocket::ShareAddress |
                          QUdpSocket::ReuseAddressHint);

    connect(&BroadcastSocket, SIGNAL(readyRead()), this, SLOT(ReadDatagram())); //for establishing connection
    BroadcastTimer.setInterval(BroadcastInterval);
    connect(&BroadcastTimer, SIGNAL(timeout()), this, SLOT(SendDatagram())); //for broadcasting writer
}

void Transmitter::TransSetNickname(const QString &pNickname)
{
    Nickname = pNickname;
}

void Transmitter::ReadDatagram()
{
    while(BroadcastSocket.hasPendingDatagrams())
    {
        QHostAddress SenderIP;
        quint16 SenderClientPort;
        QByteArray Datagram;

        Datagram.resize(BroadcastSocket.pendingDatagramSize());
        if (BroadcastSocket.readDatagram(Datagram.data(), Datagram.size(),
                                         &SenderIP, &SenderClientPort) == -1)
               continue;

        int SenderServerPort;
        QString Username;
        QCborStreamReader Reader(Datagram);

        Reader.enterContainer();

        while (Reader.readString().status == QCborStreamReader::Ok)
        {
          //reading data into reader
        }

        SenderServerPort = Reader.toInteger();

        if(IsLocalHost(SenderIP) && SenderServerPort == ListenPort)
            continue;

        if(!client->ClientHasConnectionCheck(SenderIP, SenderServerPort))
        {
            Connection *connection = new Connection(this);
            qDebug() << "[TRANSMITTER]readDatagram connection invoked " << endl;
            emit NewConnection(connection);
            connection->connectToHost(SenderIP, SenderServerPort);
        }
    }
}

void Transmitter::SendDatagram()
{
    qDebug() << "transmitter send datagram" << endl;
    QByteArray Datagram;

    QCborStreamWriter Writer(&Datagram);
    Writer.startArray(2);
    Writer.append(Nickname);
    Writer.append(ListenPort);
    Writer.endArray();

    bool UpdateAddressesFlag = false;

    for(QHostAddress addr : BroadcastAddrList)
    {
        if (BroadcastSocket.writeDatagram(Datagram, addr, BroadcastPort) == -1)
            UpdateAddressesFlag = true; //getAllAddresses() can't be called inside
    }                                   //cause it would mess up the already valid addresses

    if(UpdateAddressesFlag)
        GetAllAddresses();
}

void Transmitter::GetAllAddresses()
{
    BroadcastAddrList.clear();
    IpAddrList.clear();

    for(QNetworkInterface interface : QNetworkInterface::allInterfaces())
    {
        for(QNetworkAddressEntry addressStruct : interface.addressEntries())
        {
            QHostAddress broadcastAddress = addressStruct.broadcast();
            if (broadcastAddress != QHostAddress::Null && addressStruct.ip() != QHostAddress::LocalHost)
            {
                BroadcastAddrList.append(broadcastAddress);
                IpAddrList.append(addressStruct.ip());
            }
        }
    }
}

bool Transmitter::IsLocalHost(const QHostAddress &address)
{
    for(QHostAddress local : IpAddrList)
    {
        if(address.isEqual(local))
            return true;
    }
    return false;
}

void Transmitter::StartBroadcast()
{
    BroadcastTimer.start();
    qDebug() << "[startBroadcast] invoked" << endl;
}

void Transmitter::SetListenPort(int port)
{
    ListenPort = port;
}

QString Transmitter::GetUsername() const
{
    return Nickname;
}


