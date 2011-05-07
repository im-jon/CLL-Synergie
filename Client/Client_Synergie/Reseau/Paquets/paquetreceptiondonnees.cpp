#include "paquetreceptiondonnees.h"

PaquetReceptionDonnees::PaquetReceptionDonnees(int id) :
    BasePaquet(10)
{
    *m_Stream << id;
}
