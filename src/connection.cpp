#include "connection.h"
#include <QtNetwork>

static const int TransferTimeout = 30 * 1000;

Connection::Connection(QObject *parent) : QTcpSocket (parent), writer(this)
{
    incomingConnectionUsername = "unknown";
    greetingMsg = "undefined";
    state = WaitingGreeting;
    type = Undefined;
    isGreetingSent = false;
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
    if(isGreetingSent)
    {
        writer.endArray();
        waitForBytesWritten(3000);
    }
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

QString Connection::getIncomingConnectionUsername() const
{
    return incomingConnectionUsername;
}

void Connection::processReadyRead()
{
    reader.reparse();

    while(reader.lastError() == QCborError::NoError)
    {
        if(state == WaitingGreeting)
        {
            if(!reader.isArray())
                break;

            reader.enterContainer();
            state = ParsingGreeting;
        }
        else if (reader.containerDepth() == 1) //message and greeting both have depth 1
        {
            if (!reader.hasNext()) //if it's the end of the transmission
            {
                reader.leaveContainer();
                disconnectFromHost();
                return;
            }

            reader.enterContainer();
        }
        else if (type == Undefined) //deducing data type which comes next
        {
            if(!reader.isInteger())
                break;

            type = DataTypes(reader.toInteger());
            reader.next();
        }
        else //read datagram content
        {
            if(reader.isString())
            {
                auto r = reader.readString();
                readBuffer += r.data;
                if(r.status != QCborStreamReader::EndOfString)
                    continue;
            }
            else if (reader.isNull())
            {
                reader.next();
            }
            else
                break;

            reader.leaveContainer();

            if(transferTimerID != -1)
            {
                killTimer(transferTimerID);
                transferTimerID = -1;
            }

            if (state == ParsingGreeting)
            {
                if (type != Greeting)
                    break;
                processGreeting();
            }
            else
                processData();
        }
    }

    if (transferTimerID != -1 && reader.containerDepth() > 1)
        transferTimerID = startTimer(TransferTimeout);
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

void Connection::setGreetingMsg(const QString &grMsg)
{
    greetingMsg = grMsg;
}
