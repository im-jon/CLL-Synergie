#include "paquetenvoichat.h"

PaquetEnvoiChat::PaquetEnvoiChat(QString message):
    BasePaquet((qint8)10)
{
    *m_Stream << message;
}
