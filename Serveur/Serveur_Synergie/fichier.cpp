#include "fichier.h"

Fichier::Fichier(int id, QString chemin, QObject *parent) :
    QObject(parent)
{
    m_ID = id;
    m_Chemin = chemin;
}

QString Fichier::getChemin()
{
    return m_Chemin;
}

int Fichier::getID()
{
    return m_ID;
}
