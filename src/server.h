#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Connection;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);

signals:
    void newConnection(Connection *connection);

private slots:
    void startListening();

protected:
    void incomingConnection(qintptr handle) override;
};

#endif
