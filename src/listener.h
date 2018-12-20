#ifndef LISTENER_H
#define LISTENER_H

#include <QTcpServer>

class Listener : public QTcpServer
{
    Q_OBJECT

public:
    Listener(QObject *parent = nullptr);

signals:
    //void newConnection(Connection *connection);

protected:
    void incomingConnection(qintptr handle) override;
};

#endif // LISTENER_H
