#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"
#include "nicknamedialog.h"
#include <QHash>
#include <QHostAddress>
#include <QHostInfo>

class Transmitter;

class Client : public QObject
{
    Q_OBJECT

public:
    Client();

    void SendMessage(const QString &message);
    QString FullLocalNickname() const;
    bool ClientHasConnectionCheck(const QHostAddress &senderIP, int senderPort) const;
    static Server* GetServerInstance();

signals:
    void NewMessage(const QString &from, const QString &message);
    void NewParticipant(const QString &nick);
    void ParticipantLeft(const QString &nick);

private slots:
    void NewConnection(Connection *connection);
    void ConnectionReady();
    void Disconnected();

private:
    Transmitter *Transmitter;
    static Server* server;
    QMultiHash<QHostAddress, Connection*> Peers;
    QString Fullname;

    void RemoveConnection(Connection *connection);

};

#endif // CLIENT_H
