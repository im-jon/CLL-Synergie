#include "curseur.h"
#include "Platform.h"
#include <QDebug>

Curseur::Curseur(int id, int position, QColor couleur)
{
    m_ID = id;
    m_Position = position;
    m_Couleur = ColourAllocated(ColourDesired(
                                    couleur.red(),
                                    couleur.green(),
                                    couleur.blue()).AsLong());
}

int Curseur::getID()
{
    return m_ID;
}

int Curseur::getPosition()
{
    return m_Position;
}

int Curseur::getLigne()
{
    return m_Ligne;
}

ColourAllocated Curseur::getCouleur()
{
    return m_Couleur;
}

void Curseur::setPosition(int position)
{
    m_Position = position;
}

void Curseur::setLigne(int ligne)
{
    m_Ligne = ligne;
}

void Curseur::setIndex(int index)
{
    m_Index = index;
}
