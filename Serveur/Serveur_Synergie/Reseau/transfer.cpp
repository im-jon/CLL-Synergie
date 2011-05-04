#include "transfer.h"
#include <QDebug>
#include "serveursynergie.h"


Transfer::Transfer(Fichier* fichier)
{
    m_Fini = false;
    m_Fichier = fichier;
    QTextStream* stream = new QTextStream(fichier->getContenu());
    m_Stream = stream;
}

QString Transfer::LireBloc()
{
    QString donnees = m_Stream->read(1024);

    if (donnees.length() < 1024) {
        m_Fini = true;
    }
    return donnees;
}

bool Transfer::estFini()
{
    return m_Fini;
}

Fichier* Transfer::getFichier()
{
    return m_Fichier;
}
