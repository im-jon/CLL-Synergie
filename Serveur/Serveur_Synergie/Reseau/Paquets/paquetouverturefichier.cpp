#include "paquetouverturefichier.h"
#include "serveursynergie.h"

PaquetOuvertureFichier::PaquetOuvertureFichier(QString fichier)
    : BasePaquetServeur((qint8)10)
{
    *m_Stream << ServeurSynergie::getInstance()->getFichiers()->key(fichier);
    *m_Stream << QString(QFile("Projets/" + ServeurSynergie::getInstance()->getProjet()).readAll());
}
