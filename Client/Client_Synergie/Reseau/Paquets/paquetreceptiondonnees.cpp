#include "paquetreceptiondonnees.h"

PaquetReceptionDonnees::PaquetReceptionDonnees(int id) :
    BasePaquet((qint8)10)
{
    *m_Stream << id;
}
