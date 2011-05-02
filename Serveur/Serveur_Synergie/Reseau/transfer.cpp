#include "transfer.h"
#include <QDebug>
#include "serveursynergie.h"


Transfer::Transfer(int id)
{
    m_Fini = false;
    QString fichier = ServeurSynergie::getInstance()->getFichiers()->value(id);
    fichier = "Projets/" + ServeurSynergie::getInstance()->getProjet() + fichier;
    m_Fichier = new QFile(fichier);
    m_Fichier->open(QIODevice::ReadOnly);
    QTextStream* stream = new QTextStream(m_Fichier);
    m_Stream = stream;
    m_FeuilleID = id;
}

QString Transfer::LireBloc()
{
    QString donnees = m_Stream->read(1024);
    qDebug() << donnees.length();
    if (donnees.length() < 1024) {
        m_Fini = true;
    }
    return donnees;
}

bool Transfer::getFini()
{
    return m_Fini;
}

int Transfer::getFeuilleID()
{
    return m_FeuilleID;
}
