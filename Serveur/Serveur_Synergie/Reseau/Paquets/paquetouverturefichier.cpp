#include "paquetouverturefichier.h"
#include "serveursynergie.h"
#include <QStringBuilder>
#include <QFile>
#include <QTextStream>

PaquetOuvertureFichier::PaquetOuvertureFichier(Fichier* fichier)
    : BasePaquetServeur((qint8)10)
{
    *m_Stream << fichier->getID();
}
