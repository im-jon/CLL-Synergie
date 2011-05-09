#include "paquetmessagechat.h"

PaquetMessageChat::PaquetMessageChat(Client* auteur, QString message) :
    BasePaquet(16)
{
    *m_Stream << auteur->getID();
    *m_Stream << message;
}
