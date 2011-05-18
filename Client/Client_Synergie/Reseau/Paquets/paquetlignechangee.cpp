#include "paquetlignechangee.h"

PaquetLigneChangee::PaquetLigneChangee(int feuille, int ligne):
    BasePaquet(20)
{
    *m_Stream << feuille;
    *m_Stream << ligne;
}
