#include "serveursynergie.h"
#include "Console/console.h"
#include "Reseau/Paquets/paquetenvoicollegues.h"

ServeurSynergie* ServeurSynergie::m_Instance = 0;

// Fonction pour obtenir le Singleton du Serveur.
ServeurSynergie* ServeurSynergie::getInstance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
            m_Instance = new ServeurSynergie;
        mutex.unlock();
    }

    return m_Instance;
}

ServeurSynergie::ServeurSynergie(QObject *parent) :
    QObject(parent)
{
    m_GenerateurID = 0;
    m_Ecouteur = new QTcpServer(this);
    m_Clients = new QMap<int, Client*>();
    m_MangePaquets = new MangePaquetsServeur(this);

    connect (m_Ecouteur, SIGNAL(newConnection()), this, SLOT(slNouveauClient()));
}

bool ServeurSynergie::Demarrer()
{
    if (m_Ecouteur->listen(QHostAddress::Any, 9001)) {
        Console::getInstance()->Imprimer("Le serveur est en ligne");
        return true;
    }
    Console::getInstance()->Imprimer("Le serveur est incapable de se connecter");
    return false;
}

bool ServeurSynergie::Arreter()
{
    if (m_Ecouteur->isListening()) {
        m_Ecouteur->close();

        Console::getInstance()->Imprimer("Le serveur est hors ligne");

        return true;
    }
    return false;
}

bool ServeurSynergie::EnleverClient(Client *client)
{
    if (m_Clients->remove(client->getID()) >= 1) {
        return true;
    }
    return false;
}

void ServeurSynergie::slNouveauClient()
{
    QTcpSocket* socket = m_Ecouteur->nextPendingConnection();

    Client* client = new Client(m_GenerateurID, socket);
    Console::getInstance()->Imprimer(socket->peerAddress().toString() + " est en ligne");
    m_Clients->insert(m_GenerateurID, client);

    Console::getInstance()->Imprimer(socket->peerAddress().toString() + " est en ligne");

    m_GenerateurID++;
}

MangePaquetsServeur* ServeurSynergie::getMangePaquets()
{
    return m_MangePaquets;
}

QMap<int, Client*>* ServeurSynergie::getClients()
{
    return m_Clients;
}
