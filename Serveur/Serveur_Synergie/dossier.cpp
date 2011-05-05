#include "dossier.h"

int Dossier::GenerateurID = 0;

Dossier::Dossier(QString chemin, QObject *parent) :
    QObject(parent)
{
    m_ID = GenerateurID;
    m_Chemin = chemin;
    m_Fichiers = new QMap<int, Fichier*>;
    m_Dossiers = new QMap<int, Dossier*>;

    GenerateurID++;
}

int Dossier::getGenerateurID()
{
    return GenerateurID;
}
