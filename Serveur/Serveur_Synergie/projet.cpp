#include <QDirIterator>
#include "projet.h"

Projet::Projet(QString nom, QObject *parent) :
    QObject(parent)
{
    m_Nom = nom;
    m_Chemin = "Projets/" + nom + "/";
    m_Fichiers = new QMap<int, Fichier*>;

    Initialiser();
}

void Projet::Initialiser()
{
    // Rien qui marche la dedans...
    QRegExp regex(m_Chemin + "(.*)");
    QDirIterator iterateur(
                m_Chemin,
                (QDir::NoDotAndDotDot | QDir::Files),
                QDirIterator::Subdirectories);
    while (iterateur.hasNext())
    {
        iterateur.next();
        regex.indexIn(iterateur.filePath());
        QString chemin = regex.capturedTexts().at(1);
        Fichier* fichier = new Fichier(chemin, this);
        m_Fichiers->insert(fichier->getID(), fichier);
    }
}

void Projet::Sauvegarder()
{
    QMapIterator<int, Fichier*> iterateur(*m_Fichiers);
    while (iterateur.hasNext())
    {
        iterateur.next();
        iterateur.value()->Sauvegarder();
    }
}

void Projet::Fermer()
{
    QMapIterator<int, Fichier*> iterateur(*m_Fichiers);
    while (iterateur.hasNext())
    {
        iterateur.next();
        iterateur.value()->Fermer();
    }
}

void Projet::AjouterFichier(Fichier* fichier)
{
    m_Fichiers->insert(fichier->getID(), fichier);
}

void Projet::EnleverFichier(int id)
{
    m_Fichiers->remove(id);
}

Fichier* Projet::getFichier(int id)
{
    return m_Fichiers->value(id);
}

QString Projet::getNom()
{
    return m_Nom;
}

QString Projet::getChemin()
{
    return m_Chemin;
}

QMap<int, Fichier*>* Projet::getFichiers()
{
    return m_Fichiers;
}
