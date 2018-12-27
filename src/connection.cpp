#include "connection.h"
#include <QtNetwork>

static const int TransferTimeout = 30 * 1000;

Connection::Connection(QObject *parent) : QTcpSocket (parent), Writer(this) //for normal connection
{
    IncomingConnectionUsername = "unknown";
    GreetingMsg = "undefined";
    State = WaitingGreeting;
    Type = Undefined;
    IsGreetingSent = false;
    TransferTimerID = -1;

    QObject::connect(this, SIGNAL(connected()), this, SLOT(SendGreeting())); //for greeting
    QObject::connect(this, SIGNAL(readyRead()), this, SLOT(ProcessReadyRead())); //after greeting signals, for reading content
}

Connection::Connection(qintptr handle, QObject *parent) : Connection(parent) //for connection setup
{
    setSocketDescriptor(handle);
    Reader.setDevice(this);
}

Connection::~Connection()
{
    if(IsGreetingSent)
    {
        Writer.endArray();
        waitForBytesWritten(2000);
    }
}

void Connection::ProcessData()
{
    if(Type == Message)
        emit NewMessage(IncomingConnectionUsername, ReadBuffer);
    else
    {
        return; //
    }

    Type = Undefined;
    ReadBuffer.clear();
}

QString Connection::GetIncomingConnectionUsername() const
{
    return IncomingConnectionUsername;
}

void Connection::ProcessReadyRead()
{
    Reader.reparse();

    while(Reader.lastError() == QCborError::NoError)
    {
        if(State == WaitingGreeting)
        {
            if(!Reader.isArray())
                break;

            Reader.enterContainer();
            State = ParsingGreeting;
        }
        else if (Reader.containerDepth() == 1) //message and greeting both have depth 1
        {
            if (!Reader.hasNext()) //if it's the end of the transmission
            {
                Reader.leaveContainer();
                disconnectFromHost();
                return;
            }

            Reader.enterContainer();
        }
        else if (Type == Undefined) //deducing data type which comes next
        {
            if(!Reader.isInteger())
                break;

            Type = DataTypes(Reader.toInteger());
            Reader.next();
        }
        else //read datagram content
        {
            if(Reader.isString())
            {
                auto r = Reader.readString();
                ReadBuffer += r.data;
                if(r.status != QCborStreamReader::EndOfString)
                    continue;
            }
            else if (Reader.isNull())
            {
                Reader.next();
            }
            else
                break;

            Reader.leaveContainer();

            if(TransferTimerID != -1)
            {
                killTimer(TransferTimerID);
                TransferTimerID = -1;
            }

            if (State == ParsingGreeting)
            {
                if (Type != Greeting)
                    break;
                ProcessGreeting();
            }
            else
                ProcessData();
        }
    }

    if (TransferTimerID != -1 && Reader.containerDepth() > 1)
        TransferTimerID = startTimer(TransferTimeout);
}

void Connection::SendGreeting()
{
    Writer.startArray();

    Writer.startMap(1);
    Writer.append(Greeting);
    Writer.append(GreetingMsg);
    Writer.endMap();

    IsGreetingSent = true;

    if(!Reader.device())
        Reader.setDevice(this);
}

bool Connection::SendMessage(const QString &message)
{
    if(message.isEmpty())
        return false;

    Writer.startMap(1);
    Writer.append(Message);
    Writer.append(message);
    Writer.endMap();
    return true;
}

void Connection::ProcessGreeting()
{
    IncomingConnectionUsername = ReadBuffer + '@' + peerAddress().toString()
            + ':' + QString::number(peerPort());

    Type = Undefined;
    ReadBuffer.clear();

    if(!IsGreetingSent)
        SendGreeting();

    State = ConnectionReady;
    emit connectionReady();
}

void Connection::SetGreetingMsg(const QString &grMsg)
{
    GreetingMsg = grMsg;
}
