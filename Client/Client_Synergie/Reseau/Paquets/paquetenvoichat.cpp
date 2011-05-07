#include "paquetenvoichat.h"

PaquetEnvoiChat::PaquetEnvoiChat(QString message):
    BasePaquet(10)
{
    *m_Stream << message;
}
