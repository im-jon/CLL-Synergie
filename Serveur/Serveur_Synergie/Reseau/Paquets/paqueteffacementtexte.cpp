#include "paqueteffacementtexte.h"

PaquetEffacementTexte::PaquetEffacementTexte(Client* auteur, Fichier* fichier, int position, int longeur) :
    BasePaquet(7)
{
    *m_Stream << auteur->getID();
    *m_Stream << fichier->getID();
    *m_Stream << position;
    *m_Stream << longeur;
}
