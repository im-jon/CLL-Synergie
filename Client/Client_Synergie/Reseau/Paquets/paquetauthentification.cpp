#include "paquetauthentification.h"

PaquetAuthentification::PaquetAuthentification(QString nom, QColor couleur) :
    BasePaquet(1)
{
    *m_Stream << nom;
    *m_Stream << couleur;
}
