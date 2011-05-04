#include "collegue.h"

Collegue::Collegue(int id, QString nom, QObject *parent) :
    QObject(parent)
{
    m_ID = id;
    m_Nom = nom;
}

int Collegue::getID()
{
    return m_ID;
}

QString Collegue::getNom()
{
    return m_Nom;
}
