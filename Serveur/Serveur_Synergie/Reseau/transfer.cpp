#include "transfer.h"
#include <QDebug>
#include "serveursynergie.h"


Transfer::Transfer(Fichier* fichier)
{
    m_Fini = false;
    m_Fichier = fichier;

    QString chemin = "Projets/" + ServeurSynergie::getInstance()->getProjet() + fichier->getChemin();

    QFile* qfichier = new QFile(chemin);
    qfichier->open(QIODevice::ReadOnly);

    QTextStream* stream = new QTextStream(qfichier);
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
