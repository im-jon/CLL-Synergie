#include "paquetchangernom.h"

PaquetChangerNom::PaquetChangerNom(QString nom) :
    BasePaquet((qint8)1)
{
    *m_Stream << nom;
}
