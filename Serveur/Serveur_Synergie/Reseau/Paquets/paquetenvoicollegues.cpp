#include "paquetenvoicollegues.h"
#include <QMapIterator>
#include "client.h"
#include "serveur.h"
#include <QDebug>

PaquetEnvoiCollegues::PaquetEnvoiCollegues(Client* destinataire) :
    BasePaquet(1)
{
    *m_Stream << Serveur::Instance()->getClients()->compte() - 1;

    QMapIterator<int, Client*> iterateur(*Serveur::Instance()->getClients()->getClients());
    while (iterateur.hasNext())
    {
        iterateur.next();
        if (iterateur.value() != destinataire)
        {
            *m_Stream << iterateur.value()->getID();
            *m_Stream << iterateur.value()->getNom();
            *m_Stream << iterateur.value()->getCouleur();
        }
    }
}
