#include "paquetfermerfichier.h"

PaquetFermerFichier::PaquetFermerFichier(int id):
    BasePaquet(12)
{
    *m_Stream<<id;
}
