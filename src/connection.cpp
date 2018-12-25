#include "connection.h"
#include <QtNetwork>

Connection::Connection(QObject *parent) : QTcpSocket (parent), writer(this)
{
    incomingConnectionUsername = "unknown";
    transferTimerID = -1;

    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(processReadyRead()));
    QObject::connect(this, SIGNAL(connected()), this, SLOT(sendGreeting()));
}

Connection::Connection(qintptr handle, QObject *parent) : Connection(parent)
{
    setSocketDescriptor(handle);
    reader.setDevice(this);
}

Connection::~Connection()
{
    writer.endArray();
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
    if(type == Message)
        emit newMessage(incomingConnectionUsername, readBuffer);
    else
    {
        return; //
    }

    type = Undefined;
    readBuffer.clear();
}

QString Connection::getIncomingConnectionUsername() const //mozda nepotrebno
{
    return incomingConnectionUsername;
}

void Connection::processReadyRead()
{
    reader.reparse();


}

void Connection::sendGreeting()
{
    writer.startArray();

    writer.startMap(1);
    writer.append(Greeting);
    writer.append(greetingMsg);
    writer.endMap();

    isGreetingSent = true;

    if(!reader.device())
        reader.setDevice(this);
}

void Connection::processGreeting()
{
    incomingConnectionUsername = readBuffer + '@' + peerAddress().toString()
            + ':' + QString::number(peerPort());

    type = Undefined;
    readBuffer.clear();

    if(!isGreetingSent)
        sendGreeting();

    state = ConnectionReady;
    emit connectionReady();
}
