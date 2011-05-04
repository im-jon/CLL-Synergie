#include "paqueteffacementtexte.h"

PaquetEffacementTexte::PaquetEffacementTexte(int id, int position, int longeur) :
    BasePaquet((qint8)4)
{
    *m_Stream << id;
    *m_Stream << position;
    *m_Stream << longeur;
}
