#include "paquetlistefichiers.h"
#include "serveursynergie.h"
#include <QDebug>

PaquetListeFichiers::PaquetListeFichiers()
    : BasePaquetServeur((qint8)2)
{
    *m_Stream << ServeurSynergie::getInstance()->getFichiers()->count();

    QMapIterator<int, QString> iterateur(*ServeurSynergie::getInstance()->getFichiers());
    while (iterateur.hasNext()) {
        iterateur.next();
        *m_Stream << iterateur.key();
        *m_Stream << iterateur.value();
    }
}
