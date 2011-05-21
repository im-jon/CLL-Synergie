#include "paquetinsertiontexte.h"

PaquetInsertionTexte::PaquetInsertionTexte(Client* auteur, Fichier* fichier, QString texte, int position) :
    BasePaquet(5)
{
    *m_Stream << auteur->getID();
    *m_Stream << fichier->getID();
    *m_Stream << position;
    *m_Stream << texte;
}
