#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QTimer>

class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    enum DataTypes
    {
        Message, Greeting, Undefined
    };

    enum ConnectionStates
    {
        WaitingGreeting, ParsingGreeting, ConnectionReady
    };

    Connection(QObject *parent = nullptr);
    Connection(qintptr handle, QObject *parent = nullptr);
    ~Connection();

    QString GetIncomingConnectionUsername() const;
    bool SendMessage(const QString &message);
    void SetGreetingMsg(const QString &grMsg);

private slots:
    void ProcessReadyRead();
    void SendGreeting();

signals:
    void NewMessage(const QString &from, const QString &message);
    void connectionReady();

private:
    QCborStreamReader Reader;
    QCborStreamWriter Writer;
    QString ReadBuffer;
    DataTypes Type;
    ConnectionStates State;
    int TransferTimerID;
    QString IncomingConnectionUsername;
    QString GreetingMsg;
    bool IsGreetingSent;

    void ProcessData();
    void ProcessGreeting();
};

#endif // CONNECTION_H
