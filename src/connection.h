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
        Message, Greeting, Ping, Pong, Undefined
    };

    Connection(QObject *parent = nullptr);
    Connection(qintptr handle, QObject *parent = nullptr);
    ~Connection();

    QString getFullName() const;
    bool sendMessage(const QString &message);

private slots:
    void sendPing();
    void processData();

signals:
    void newMessage(const QString &from, const QString &message);
    void connectionReady();

private:
    QCborStreamReader reader;
    QCborStreamWriter writer;
    QString readBuffer;
    QString nick;
    DataTypes type;
    QTimer pingTimer;
    int transferTimerID;
    QString fullName;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // CONNECTION_H
