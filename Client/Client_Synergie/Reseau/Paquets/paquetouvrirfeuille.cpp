#include "paquetouvrirfeuille.h"

PaquetOuvrirFeuille::PaquetOuvrirFeuille(int id) :
    BasePaquet(7)
{
    *m_Stream << id;
}
