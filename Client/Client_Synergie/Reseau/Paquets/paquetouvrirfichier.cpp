#include "paquetouvrirfichier.h"

PaquetOuvrirFichier::PaquetOuvrirFichier(int id) :
    BasePaquet((qint8)7)
{
    *m_Stream << id;
}
