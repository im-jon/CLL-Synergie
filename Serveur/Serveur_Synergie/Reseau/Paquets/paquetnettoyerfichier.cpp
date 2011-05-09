#include "paquetnettoyerfichier.h"

PaquetNettoyerFichier::PaquetNettoyerFichier(Fichier* fichier) :
    BasePaquet(17)
{
    *m_Stream << fichier->getID();
}
