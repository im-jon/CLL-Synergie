#include "paquetfermerfeuille.h"

PaquetFermerFeuille::PaquetFermerFeuille(Client* client, Fichier* fichier) :
    BasePaquet(20)
{
    *m_Stream << client->getID();
    *m_Stream << fichier->getID();
}
