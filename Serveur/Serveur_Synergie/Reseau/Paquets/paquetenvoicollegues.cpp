#include "paquetenvoicollegues.h"
#include <QMapIterator>
#include "Reseau/client.h"
#include "serveursynergie.h"

PaquetEnvoiCollegues::PaquetEnvoiCollegues() :
    BasePaquetServeur((qint8)1)
{
    *m_Stream << ServeurSynergie::getInstance()->getClients()->count();

    QMapIterator<int, Client*> iterateur(*ServeurSynergie::getInstance()->getClients());
    while (iterateur.hasNext()) {
        iterateur.next();
        *m_Stream << iterateur.value()->getNom();
    }
}
