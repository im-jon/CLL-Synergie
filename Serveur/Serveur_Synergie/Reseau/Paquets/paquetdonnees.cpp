#include "paquetdonnees.h"

PaquetDonnees::PaquetDonnees(Transfer* transfer)
    : BasePaquetServeur((qint8)15)
{
    *m_Stream << transfer->getFichier()->getID();
    *m_Stream << transfer->LireBloc();
}
