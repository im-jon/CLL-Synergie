#ifndef PAQUETMESSAGECHAT_H
#define PAQUETMESSAGECHAT_H

#include "basepaquet.h"
#include "../client.h"

class PaquetMessageChat : public BasePaquet
{
public:
    PaquetMessageChat(Client* auteur, QString message);
};

#endif // PAQUETMESSAGECHAT_H
