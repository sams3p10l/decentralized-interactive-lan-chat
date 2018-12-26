#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include <QHash>
#include <QHostAddress>
#include <QHostInfo>

class Transmitter;

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

    void sendMessage(const QString &message);
    QString fullLocalNickname() const;
    bool clientHasConnectionCheck(const QHostAddress &senderIP, int senderPort) const;

signals:
    void newMessage(const QString &from, const QString &message);
    void newParticipant(const QString &nick);
    void participantLeft(const QString &nick);
    void startListening();

private slots:
    void newConnection(Connection *connection);
    void connectionReady();
    void disconnected();
    void transmitterStartBroadcast();
    void startListeningSlot();

private:
    Transmitter *transmitter;
    Server server;
    QMultiHash<QHostAddress, Connection*> peers;
    QString fullname;

    void removeConnection(Connection *connection);

};

#endif // CLIENT_H
