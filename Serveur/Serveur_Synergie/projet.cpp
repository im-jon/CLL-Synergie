#include <QDirIterator>
#include "projet.h"

Projet::Projet(QString nom, QObject *parent) :
    QObject(parent)
{
    m_Nom = nom;
    m_Fichiers = new QMap<int, Fichier*>;
    m_Elements = new QStringList;
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
        QString chemin = regex.capturedTexts().at(1);
        m_Elements->append(chemin);
        if (iterateur.fileInfo().isFile()) {
            Fichier* fichier = new Fichier(chemin, this);
            m_Fichiers->insert(fichier->getID(), fichier);
        }
    }
    qDebug() << m_Elements->count();
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

QMap<int, Fichier*>* Projet::getFichiers()
{
    return m_Fichiers;
}
