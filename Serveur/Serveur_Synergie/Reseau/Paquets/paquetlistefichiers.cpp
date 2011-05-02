#include "paquetlistefichiers.h"
#include "serveursynergie.h"

PaquetListeFichiers::PaquetListeFichiers()
    : BasePaquetServeur((qint8)2)
{
    *m_Stream << ServeurSynergie::getInstance()->getFichiers()->count();

    QMapIterator<int, QString> iterateur(*ServeurSynergie::getInstance()->getFichiers());
    while (iterateur.hasNext()) {
        iterateur.next();
        *m_Stream << iterateur.value();
    }
}
