#include "paquetlistefichiers.h"
#include "serveursynergie.h"
#include <QDebug>
#include "fichier.h"

PaquetListeFichiers::PaquetListeFichiers()
    : BasePaquetServeur((qint8)2)
{
    *m_Stream << ServeurSynergie::getInstance()->getProjet()->getFichiers()->count();

    QMapIterator<int, Fichier*> iterateur(*ServeurSynergie::getInstance()->getProjet()->getFichiers());
    while (iterateur.hasNext())
    {
        iterateur.next();
        *m_Stream << iterateur.key();
        *m_Stream << iterateur.value()->getChemin();
    } 
}
