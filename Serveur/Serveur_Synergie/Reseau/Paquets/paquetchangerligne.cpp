#include "paquetchangerligne.h"

PaquetChangerLigne::PaquetChangerLigne(Client* client, Fichier* fichier) :
    BasePaquet(18)
{
    *m_Stream << client->getID();
    *m_Stream << fichier->getID();
    *m_Stream << fichier->getCurseur(client)->getLigne();
}
