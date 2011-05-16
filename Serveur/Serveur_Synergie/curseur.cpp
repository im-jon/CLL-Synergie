#include "curseur.h"

Curseur::Curseur(Client* client)
{
    m_Client = client;
}

int Curseur::getIndex()
{
    return m_Index;
}

int Curseur::getLigne()
{
    return m_Ligne;
}

void Curseur::setLigne(int ligne)
{
    m_Ligne = ligne;
}

void Curseur::setIndex(int index)
{
    m_Index = index;
}
