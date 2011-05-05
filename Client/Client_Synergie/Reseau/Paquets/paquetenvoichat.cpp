#include "paquetenvoichat.h"

paquetEnvoiChat::paquetEnvoiChat(QString Texte):
    BasePaquet((qint8)10)
{
    *m_Stream << Texte;
}
