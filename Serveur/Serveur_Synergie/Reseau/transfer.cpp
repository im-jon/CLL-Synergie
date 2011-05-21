#include "transfer.h"

static const int TailleBloc = 1024; // Taille des blocs de texte en octets

Transfer::Transfer(Fichier* fichier, QObject *parent) :
    QObject(parent)
{
    m_Fichier = fichier;

    // Nous utilisons un QTextStream pour lire le fichier en petits blocs
    m_Stream = new QTextStream(fichier->getContenu());
}

QString Transfer::LireBloc()
{
    QString donnees = m_Stream->read(TailleBloc);

    // Si la taille du bloc de texte est inférieur à la taille imposée,
    // cela signifie que le transfer est terminé
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
