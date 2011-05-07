#include "paquetdonnees.h"

PaquetDonnees::PaquetDonnees(Transfer* transfer)
    : BasePaquet(15)
{
    *m_Stream << transfer->getFichier()->getID();
    *m_Stream << transfer->LireBloc();
}
