#include "paquetchangernom.h"

PaquetChangerNom::PaquetChangerNom(QString nom) :
    BasePaquet(1)
{
    *m_Stream << nom;
}
