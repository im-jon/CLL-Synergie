#include "paquetenvoicollegues.h"
#include <QMapIterator>
#include "client.h"
#include "serveur.h"
#include <QDebug>

PaquetEnvoiCollegues::PaquetEnvoiCollegues() :
    BasePaquet(1)
{
    *m_Stream << Serveur::Instance()->getClients()->compte();

    QMapIterator<int, Client*> iterateur(*Serveur::Instance()->getClients()->getClients());
    while (iterateur.hasNext())
    {
        iterateur.next();
        *m_Stream << iterateur.value()->getID();
        *m_Stream << iterateur.value()->getNom();
    }
}
