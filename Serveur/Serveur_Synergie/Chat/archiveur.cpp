#include "archiveur.h"

Archiveur::Archiveur(QObject *parent) :
    QObject(parent)
{
    Initialiser();
}

void Archiveur::Initialiser()
{
    m_Repertoire = new QDir("Archives");
    if (!m_Repertoire->exists())
    {
        QDir().mkdir("Archives");
    }
}

void Archiveur::Archiver(Message *message)
{

}
