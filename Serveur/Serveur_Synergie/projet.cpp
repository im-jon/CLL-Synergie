#include <QDirIterator>
#include "projet.h"

Projet::Projet(QString nom, QObject *parent) :
    QObject(parent)
{
    m_Nom = nom;
    m_Fichiers = new QMap<int, Fichier*>;
    Initialiser();
}

void Projet::Initialiser()
{
    QRegExp regex("Projets\/.*\/(.*)");
    QDirIterator iterateur(
                "Projets/" + m_Nom + "/",
                (QDir::NoDotAndDotDot | QDir::AllEntries),
                QDirIterator::Subdirectories);
    while (iterateur.hasNext()) {
        iterateur.next();
        regex.indexIn(iterateur.filePath());
        Fichier* fichier = new Fichier(regex.capturedTexts().at(1), this);
        m_Fichiers->insert(fichier->getID(), fichier);
    }
}

void Projet::AjouterFichier(Fichier *fichier)
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
