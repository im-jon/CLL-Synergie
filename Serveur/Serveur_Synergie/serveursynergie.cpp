#include "serveursynergie.h"
#include "Console/console.h"

ServeurSynergie* ServeurSynergie::m_Instance = 0;

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
    m_ID = 0;
    m_Ecouteur = new QTcpServer();
    connect (m_Ecouteur, SIGNAL(newConnection()), this, SLOT(slNouveauClient()));
}

bool ServeurSynergie::Demarrer()
{
    Console::Instance()->Imprimer("Le serveur est en ligne");
    return m_Ecouteur->listen(QHostAddress::Any, 9001);
}

bool ServeurSynergie::Arreter()
{
    if (m_Ecouteur->isListening()) {
        m_Ecouteur->close();
        Console::Instance()->Imprimer("Le serveur est hors ligne");
        return true;
    }
    return false;
}

void ServeurSynergie::slNouveauClient()
{
    // pogne le nouveau client
    QTcpSocket* socket = m_Ecouteur->nextPendingConnection();
    Client* client = new Client(socket);
    Console::Instance()->Imprimer(socket->peerAddress().toString() + " est en ligne");
    m_Clients.insert(m_ID, client);
    m_ID++;
}
