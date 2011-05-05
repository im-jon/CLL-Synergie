#include "projet.h"

Projet::Projet(QString nom, QObject *parent) :
    QObject(parent)
{
    m_Nom = nom;
    m_DossierPrincipal = new Dossier("Projets/" + nom + "/", this);
}

void Projet::Initialiser()
{

}

QString Projet::getNom()
{
    return m_Nom;
}
