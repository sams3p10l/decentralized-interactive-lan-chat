#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include <QHash>
#include <QHostAddress>

class Transmitter;

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

    void sendMessage(const QString &message);
    bool clientHasConnectionCheck(const QHostAddress &senderIP, int senderPort) const;

signals:
    void newMessage(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);

private slots:
    void newConnection(Connection *connection);
    void connectionReady();
    void disconnected();

private:
    Transmitter *transmitter;
    Server server;
    QMultiHash<QHostAddress, Connection*> peers;
    QString fullname;

    void removeConnection(Connection *connection);

};

#endif // CLIENT_H
