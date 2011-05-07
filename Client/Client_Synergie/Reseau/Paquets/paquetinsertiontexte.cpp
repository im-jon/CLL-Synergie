#include "paquetinsertiontexte.h"

PaquetInsertionTexte::PaquetInsertionTexte(int id, int pos, QString texte):
    BasePaquet(2)
{
    *m_Stream << id;
    *m_Stream << pos;
    *m_Stream << texte;
}
