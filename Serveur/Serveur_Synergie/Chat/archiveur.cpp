#include "archiveur.h"
#include <QDateTime>

Archiveur::Archiveur(QObject *parent) :
    QObject(parent)
{
    m_Actif = false;
    m_NomFichier = QDateTime::currentDateTime().toString("dd-MM-yy");
}

void Archiveur::Demarrer()
{
    if (!m_Actif)
    {
        m_Repertoire = new QDir("Archives");
        if (!m_Repertoire->exists())
        {
            QDir().mkdir("Archives");
        }

        m_FichierActuel = new QFile("Archives/" + m_NomFichier + ".txt");
        m_FichierActuel->open(QFile::WriteOnly | QFile::Append);

        m_Stream = new QTextStream(m_FichierActuel);

        m_Actif = true;
    }
}

void Archiveur::Arreter()
{
    if (m_Actif)
    {
        m_FichierActuel->close();
        m_Actif = false;
    }
}

void Archiveur::Archiver(Message* message)
{
    if (m_Actif)
    {
        QString heure = message->getDate().toString("hh:mm:ss");
        QString ligne = "(" + heure + ") " + message->getAuteur()->getNom() + " : " + message->getContenu() + "\n";
        *m_Stream << ligne;
    }
}

void Archiveur::Archiver(QList<Message*>* messages)
{
    if (m_Actif)
    {
        Message* message;
        foreach (message, *messages)
        {
            Archiver(message);
        }
    }
}
