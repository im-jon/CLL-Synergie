#include "curseur.h"

Curseur::Curseur(int id, int ligne, QColor* couleur)
{
    m_ID = id;
    m_Couleur = couleur;
    m_Ligne = ligne;
}

int Curseur::getID()
{
    return m_ID;
}

int Curseur::getLigne()
{
    return m_Ligne;
}

QColor* Curseur::getCouleur()
{
    return m_Couleur;
}

void Curseur::setLigne(int ligne)
{
    m_Ligne = ligne;
}
