#include "transfer.h"

Transfer::Transfer(Fichier* fichier, QObject *parent) :
    QObject(parent)
{
    m_Fichier = fichier;
    QTextStream* stream = new QTextStream(fichier->getContenu());
    m_Stream = stream;
}

QString Transfer::LireBloc()
{
    QString donnees = m_Stream->read(1024);

    if (donnees.length() < 1024)
    {
        emit (siFin(m_Fichier->getID()));
    }
    return donnees;
}

Fichier* Transfer::getFichier()
{
    return m_Fichier;
}
