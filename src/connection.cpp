#include "connection.h"
#include <QtNetwork>

static const int PingInterval = 5 * 1000;
static const int PongTimeout = 60 * 1000;

Connection::Connection(QObject *parent) : QTcpSocket (parent), writer(this)
{
    nick = "unknown";
    transferTimerID = -1;
    pingTimer.setInterval(PingInterval);

    QObject::connect(&pingTimer, SIGNAL(timeout()), this, SLOT(sendPing()));
}

Connection::Connection(qintptr handle, QObject *parent) : Connection(parent)
{
    setSocketDescriptor(handle);
    reader.setDevice(this);
}

Connection::~Connection()
{

}

void Connection::sendPing()
{
    writer.startMap(1);
    writer.append(Ping);
    writer.append(nullptr);
    writer.endMap();
}

bool Connection::sendMessage(const QString &message)
{
    if(message.isEmpty())
        return false;

    writer.startMap(1);
    writer.append(Message);
    writer.append(message);
    writer.endMap();
    return true;
}

void Connection::timerEvent(QTimerEvent *timerEvent)
{
    if (timerEvent->timerId() == transferTimerID) {
        abort();
        killTimer(transferTimerID);
        transferTimerID = -1;
    }
}

void Connection::processData()
{
    switch(type)
    {
        case Message:
            emit newMessage(nick, readBuffer);
            break;
        case Ping:
            writer.startMap(1);
            writer.append(Ping);
            writer.append(nullptr);
            writer.endMap();
            break;
        case Pong:
            //
        default:
            break;
    }

    type = Undefined;
    readBuffer.clear();
}

QString Connection::getFullName() const //mozda nepotrebno
{
    return fullName;
}
