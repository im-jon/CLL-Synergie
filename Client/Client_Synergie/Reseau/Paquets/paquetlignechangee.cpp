#include "paquetlignechangee.h"

paquetLigneChangee::paquetLigneChangee(int feuille,int ligne):
    BasePaquet(20)

{
    *m_Stream << feuille;
    *m_Stream << ligne;
}
