#include "paquetouvrirfeuille.h"

PaquetOuvrirFeuille::PaquetOuvrirFeuille(int id) :
    BasePaquet((qint8)7)
{
    *m_Stream << id;
}
