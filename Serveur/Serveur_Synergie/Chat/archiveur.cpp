#include "archiveur.h"
#include <QDateTime>

Archiveur::Archiveur(QObject *parent) :
    QObject(parent)
{
    Initialiser();
}

void Archiveur::Arreter()
{
    m_FichierActuel->close();
}

void Archiveur::Initialiser()
{
    m_Repertoire = new QDir("Archives");
    if (!m_Repertoire->exists())
    {
        QDir().mkdir("Archives");
    }

    QString nom = QDateTime::currentDateTime().toString("dd-MM-yy");
    m_FichierActuel = new QFile("Archives/" + nom + ".txt");
    m_FichierActuel->open(QFile::WriteOnly | QFile::Append);
    m_Stream = new QTextStream(m_FichierActuel);
}

void Archiveur::Archiver(Message* message)
{
    QString heure = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString ligne = "(" + heure + ") " + message->getAuteur()->getNom() + " : " + message->getContenu() + "\n";
    *m_Stream << ligne;
}

void Archiveur::Archiver(QList<Message*>* messages)
{
    Message* message;
    foreach (message, *messages)
    {
        Archiver(message);
    }
}
