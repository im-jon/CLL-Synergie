#include "serveursynergie.h"
#include "Console/console.h"
#include "Reseau/Paquets/paquetenvoicollegues.h"
#include "Reseau/Paquets/paquetconnexioncollegue.h"
#include <QDir>
#include <QMapIterator>

ServeurSynergie* ServeurSynergie::m_Instance = 0;

// Fonction pour le Singleton.
ServeurSynergie* ServeurSynergie::getInstance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
        {
            m_Instance = new ServeurSynergie;
        }
        mutex.unlock();
    }

    return m_Instance;
}

ServeurSynergie::ServeurSynergie(QObject *parent) :
    QObject(parent)
{
    m_Ecouteur = new QTcpServer(this);
    m_Clients = new QMap<int, Client*>;
    m_MangePaquets = new MangePaquetsServeur(this);

    connect (m_Ecouteur, SIGNAL(newConnection()), this, SLOT(slNouveauClient()));

    QDir dossierProjets("Projets");
    if (dossierProjets.exists())
    {
        if (dossierProjets.entryList(QDir::AllDirs | QDir::NoDotAndDotDot).count() == 0)
        {
            Console::getInstance()->Imprimer("Le répertoire de projets est vide");
        }
    }
    else
    {
        QDir().mkdir("Projets");
    }

    m_Projet = new Projet("Projet1", this);
}

bool ServeurSynergie::Demarrer()
{
    if (m_Ecouteur->listen(QHostAddress::Any, 9001))
    {
        Console::getInstance()->Imprimer("Le serveur est en ligne");
        return true;
    }
    Console::getInstance()->Imprimer("Le serveur est incapable de se connecter");
    return false;
}

bool ServeurSynergie::Arreter()
{
    if (m_Ecouteur->isListening())
    {
        m_Ecouteur->close();
        Console::getInstance()->Imprimer("Le serveur est hors ligne");
        return true;
    }
    m_Projet->Fermer();
    Console::getInstance()->Imprimer("Le serveur est incapable de se déconnecter");
    return false;
}

void ServeurSynergie::slNouveauClient()
{
    Client* client = new Client(m_Ecouteur->nextPendingConnection(), this);
    AjouterClient(client);
    Console::getInstance()->Imprimer(client->getIP() + " est en ligne");
}

bool ServeurSynergie::AjouterClient(Client *client)
{
    m_Clients->insert(client->getID(), client);
}

bool ServeurSynergie::EnleverClient(Client *client)
{
    int nb = m_Clients->remove(client->getID());
    if (nb >= 1)
    {
        return true;
    }
    return false;
}

bool ServeurSynergie::NouveauProjet(QString nom)
{
    QDir dossierProjets("Projets");
    if (!dossierProjets.exists())
    {
        if (!QDir().mkdir("Projets"))
        {
            return false;
        }
    }
    return dossierProjets.mkdir(nom);
}

void ServeurSynergie::EnvoyerPaquetATous(BasePaquetServeur *paquet, Client* exception)
{
    QMapIterator<int, Client*> iterateur(*m_Clients);
    while (iterateur.hasNext())
    {
        iterateur.next();
        if (iterateur.value() != exception)
        {
            iterateur.value()->EnvoyerPaquet(paquet);
        }
    }
}

// Je pourrais être statique!
void ServeurSynergie::EnvoyerPaquetAListe(QList<Client *>* clients, BasePaquetServeur *paquet, Client *exception)
{
    Client* client;
    foreach (client, *clients)
    {
        if (client != exception)
        {
            client->EnvoyerPaquet(paquet);
        }
    }
}

MangePaquetsServeur* ServeurSynergie::getMangePaquets()
{
    return m_MangePaquets;
}

QMap<int, Client*>* ServeurSynergie::getClients()
{
    return m_Clients;
}

Projet* ServeurSynergie::getProjet()
{
    return m_Projet;
}
