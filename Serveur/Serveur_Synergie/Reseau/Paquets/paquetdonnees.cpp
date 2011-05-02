#include "paquetdonnees.h"

PaquetDonnees::PaquetDonnees(int id, QString donnees)
    : BasePaquetServeur((qint8)15)
{
    *m_Stream << id;
    *m_Stream << donnees;
}
