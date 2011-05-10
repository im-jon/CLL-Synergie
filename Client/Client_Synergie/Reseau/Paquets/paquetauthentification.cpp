#include "paquetauthentification.h"

PaquetAuthentification::PaquetAuthentification(QString nom) :
    BasePaquet(1)
{
    *m_Stream << nom;
}
