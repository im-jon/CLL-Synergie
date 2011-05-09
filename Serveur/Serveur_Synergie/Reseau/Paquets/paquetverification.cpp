#include "paquetverification.h"

PaquetVerification::PaquetVerification(Fichier* fichier) :
    BasePaquet(13)
{
    *m_Stream << fichier->getID();
    *m_Stream << fichier->longeur();
}
