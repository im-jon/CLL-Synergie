#include "paquetinsertiontexte.h"

paquetinsertiontexte::paquetinsertiontexte(int idfichier, int position, QString Texte):
    BasePaquet((qint8)2)
{
    *m_Stream << idfichier;
    *m_Stream << position;
    *m_Stream << Texte;
}
