#include "paquetmessagechat.h"

PaquetMessageChat::PaquetMessageChat(Message* message) :
    BasePaquet(16)
{
    *m_Stream << message->getAuteur()->getID();
    *m_Stream << message->getContenu();
}
