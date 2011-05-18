#include "paquetfermerfeuille.h"

PaquetFermerFeuille::PaquetFermerFeuille(int id):
    BasePaquet(12)
{
    *m_Stream << id;
}
