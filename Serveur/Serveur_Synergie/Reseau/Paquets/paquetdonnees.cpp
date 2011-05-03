#include "paquetdonnees.h"

PaquetDonnees::PaquetDonnees(Transfer* transfer)
    : BasePaquetServeur((qint8)15)
{
    *m_Stream << transfer->getFeuilleID();
    *m_Stream << transfer->LireBloc();
}
