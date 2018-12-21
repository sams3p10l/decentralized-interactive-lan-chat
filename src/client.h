#ifndef CLIENT_H
#define CLIENT_H

#include "server.h"

class Client : public QObject
{
    Q_OBJECT

public:
    Client();
};

#endif // CLIENT_H
