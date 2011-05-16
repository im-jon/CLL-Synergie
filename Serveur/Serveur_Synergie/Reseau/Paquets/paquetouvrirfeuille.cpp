#include "paquetouvrirfeuille.h"

PaquetOuvrirFeuille::PaquetOuvrirFeuille(Client* client, Fichier* fichier) :
    BasePaquet(19)
{
    *m_Stream << client->getID();
    *m_Stream << fichier->getID();
}
