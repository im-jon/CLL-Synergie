#include "paquetouverturefichier.h"
#include "serveursynergie.h"
#include <QStringBuilder>
#include <QFile>
#include <QTextStream>

PaquetOuvertureFichier::PaquetOuvertureFichier(int id)
    : BasePaquetServeur((qint8)10)
{
    *m_Stream << id;
}
