#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>
#include <QCborStreamReader>
#include <QCborStreamWriter>
#include <QTimer>

class Connection : public QTcpSocket //zasto QTcp a ne QUdp?
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

    QString getIncomingConnectionUsername() const;
    bool sendMessage(const QString &message);
    void setGreetingMsg(const QString &grMsg);

private slots:
    void processReadyRead();
    void sendGreeting();

signals:
    void newMessage(const QString &from, const QString &message);
    void connectionReady();

private:
    QCborStreamReader reader;
    QCborStreamWriter writer;
    QString readBuffer;
    DataTypes type;
    ConnectionStates state;
    QTimer pingTimer;
    int transferTimerID;
    QString incomingConnectionUsername;
    QString greetingMsg;
    bool isGreetingSent;

    void processData();
    void processGreeting();

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // CONNECTION_H
