#include "clients.h"
#include "Reseau/Paquets/paquetdeconnexioncollegue.h"

Clients::Clients(QObject *parent) :
    QObject(parent)
{
    m_Clients = new QMap<int, Client*>;
}

void Clients::AjouterClient(Client *client)
{
    m_Clients->insert(client->getID(), client);

    connect (client, SIGNAL(siDeconnexion(Client*)), this, SLOT(slDeconnexionClient(Client*)));
}

void Clients::EnleverClient(Client *client)
{
    m_Clients->remove(client->getID());
    EnvoyerPaquetATous(new PaquetDeconnexionCollegue(client));
}

void Clients::EnvoyerPaquetATous(BasePaquet* paquet, Client* exception)
{
    QByteArray ba;
    QByteArray buffer = paquet->getBuffer();
    memcpy(&ba, &buffer, sizeof(buffer));

    QMapIterator<int, Client*> iterateur(*m_Clients);
    while (iterateur.hasNext())
    {
        iterateur.next();
        if (iterateur.value() != exception)
        {
            iterateur.value()->getConnexion()->EnvoyerBytes(ba);
        }
    }
}

void Clients::EnvoyerPaquetAListe(QList<Client *>* clients, BasePaquet* paquet, Client* exception)
{
    Client* client;
    QByteArray ba;

    QByteArray buffer = paquet->getBuffer();
    memcpy(&ba, &buffer, sizeof(buffer));

    foreach (client, *clients)
    {
        if (client != exception)
        {
            client->getConnexion()->EnvoyerBytes(ba);
        }
    }
}

int Clients::compte()
{
    return m_Clients->count();
}

QMap<int, Client*>* Clients::getClients()
{
    return m_Clients;
}

void Clients::slDeconnexionClient(Client *client)
{
    EnleverClient(client);
}
