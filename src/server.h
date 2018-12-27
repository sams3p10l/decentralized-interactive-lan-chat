#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>

class Connection;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);

signals:
    void newConnection(Connection *connection);

public slots:
    void startListening();

protected:
    void incomingConnection(qintptr handle) override;
};

#endif
