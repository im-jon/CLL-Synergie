#include <QDir>
#include <QDirIterator>

#include "projet.h"
#include "Console/console.h"

Projet::Projet(QString nom, QObject *parent) :
    QObject(parent)
{
    m_Nom = nom;
    m_Chemin = "Projets/" + nom + "/";
    m_Fichiers = new QMap<int, Fichier*>;
    m_Ouvert = false;
}

bool Projet::Creer()
{
    if (!m_Ouvert)
    {
        QDir dossierProjets("Projets");
        if (!dossierProjets.exists())
        {
            QDir().mkdir("Projets");
        }
        return dossierProjets.mkdir(m_Nom);
    }
    return false;
}

bool Projet::Ouvrir()
{
    if (!m_Ouvert)
    {
        // Cette partie est considérablement mal faite
        // Pour l'instant elle produit la liste des fichiers du projet sans
        // se préoccuper de la hierarchie du projet
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

        m_Ouvert = true;
        return true;
    }
    return false;
}

bool Projet::Sauvegarder()
{
    if (m_Ouvert)
    {
        QMapIterator<int, Fichier*> iterateur(*m_Fichiers);
        while (iterateur.hasNext())
        {
            iterateur.next();
            iterateur.value()->Sauvegarder();
        }
        return true;
    }
    return false;
}

bool Projet::Fermer()
{
    if (m_Ouvert)
    {
        QMapIterator<int, Fichier*> iterateur(*m_Fichiers);
        while (iterateur.hasNext())
        {
            iterateur.next();
            iterateur.value()->Fermer();
        }
        m_Ouvert = false;
        return true;
    }
    return false;
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
