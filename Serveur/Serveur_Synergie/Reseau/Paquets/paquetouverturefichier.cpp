#include "paquetouverturefichier.h"
#include "serveursynergie.h"
#include <QStringBuilder>
#include <QFile>
#include <QTextStream>

PaquetOuvertureFichier::PaquetOuvertureFichier(int id)
    : BasePaquetServeur((qint8)10)
{
    QString fichier = ServeurSynergie::getInstance()->getFichiers()->value(id);
    QFile data("Projets/" + ServeurSynergie::getInstance()->getProjet() + fichier);
    data.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream* stream = new QTextStream(&data);

    *m_Stream << id;
    *m_Stream << stream->readAll();
}
