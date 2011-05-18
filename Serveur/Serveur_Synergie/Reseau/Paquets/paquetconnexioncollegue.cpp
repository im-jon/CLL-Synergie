#include "paquetconnexioncollegue.h"

PaquetConnexionCollegue::PaquetConnexionCollegue(Client* client) :
    BasePaquet(3)
{
    *m_Stream << client->getID();
    *m_Stream << client->getNom();
    *m_Stream << client->getCouleur();
}
