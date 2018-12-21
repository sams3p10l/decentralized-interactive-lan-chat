#include "client.h"
#include "transmitter.h"

Client::Client()
{
    transmitter = new Transmitter(this);

}
