#include "paquetenvoichat.h"

PaquetEnvoiChat::PaquetEnvoiChat(QString message):
    BasePaquet(11)
{
    *m_Stream << message;
}
