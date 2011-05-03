#include "transfer.h"
#include <QDebug>
#include "serveursynergie.h"


Transfer::Transfer(int id)
{
    m_Fini = false;
    m_FeuilleID = id;

    QString fichier = ServeurSynergie::getInstance()->getFichiers()->value(id);
    fichier = "Projets/" + ServeurSynergie::getInstance()->getProjet() + fichier;
    m_Fichier = new QFile(fichier);
    m_Fichier->open(QIODevice::ReadOnly);

    QTextStream* stream = new QTextStream(m_Fichier);
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

int Transfer::getFeuilleID()
{
    return m_FeuilleID;
}
