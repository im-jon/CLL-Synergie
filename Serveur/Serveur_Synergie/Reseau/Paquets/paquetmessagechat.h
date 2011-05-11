#ifndef PAQUETMESSAGECHAT_H
#define PAQUETMESSAGECHAT_H

#include "basepaquet.h"
#include "client.h"
#include "Chat/message.h"

class PaquetMessageChat : public BasePaquet
{
public:
    PaquetMessageChat(Message* message);
};

#endif // PAQUETMESSAGECHAT_H
