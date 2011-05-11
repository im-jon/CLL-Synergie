#include "transfer.h"

static const int TailleBloc = 512; // Octets

Transfer::Transfer(Fichier* fichier, QObject *parent) :
    QObject(parent)
{
    m_Fichier = fichier;
    QTextStream* stream = new QTextStream(fichier->getContenu());
    m_Stream = stream;
}

QString Transfer::LireBloc()
{
    QString donnees = m_Stream->read(TailleBloc);

    if (donnees.length() < TailleBloc)
    {
        emit (siFin(m_Fichier->getID()));
    }

    return donnees;
}

Fichier* Transfer::getFichier()
{
    return m_Fichier;
}
