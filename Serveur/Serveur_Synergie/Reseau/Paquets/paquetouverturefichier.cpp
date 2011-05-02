#include "paquetouverturefichier.h"
#include "serveursynergie.h"
#include <QStringBuilder>
#include <QFile>

PaquetOuvertureFichier::PaquetOuvertureFichier(int id)
    : BasePaquetServeur((qint8)10)
{
    QString fichier = ServeurSynergie::getInstance()->getFichiers()->value(id);
    *m_Stream << id;
    QString chemin = "Projets/" + ServeurSynergie::getInstance()->getProjet() + fichier;
    //*m_Stream << QString(QFile("Projets/Projet1/Connexion.cpp").readAll());
    *m_Stream << "LOL WUT";
}
