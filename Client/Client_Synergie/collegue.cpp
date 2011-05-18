#include "collegue.h"

Collegue::Collegue(int id, QString nom, QColor couleur, QObject *parent) :
    QObject(parent)
{
    m_ID = id;
    m_Nom = nom;
    m_Couleur = couleur;
}

int Collegue::getID()
{
    return m_ID;
}

QString Collegue::getNom()
{
    return m_Nom;
}

QColor Collegue::getCouleur()
{
    return m_Couleur;
}
