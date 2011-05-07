#include "feuille.h"

Feuille::Feuille(int id, QString nom, QObject *parent) :
    QObject(parent)
{
    m_ID = id;
    m_Nom = nom;
}

int Feuille::getID()
{
    return m_ID;
}

QString Feuille::getNom()
{
    return m_Nom;
}
