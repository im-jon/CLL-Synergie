#include "serveursynergie.h"

ServeurSynergie::ServeurSynergie(QObject *parent) :
    QObject(parent)
{
    m_ID = 0;
    m_Ecouteur = new QTcpServer();
    connect (m_Ecouteur, SIGNAL(newConnection()), this, SLOT(slNouveauClient()));
}

bool ServeurSynergie::Demarrer()
{
    return m_Ecouteur->listen(QHostAddress::Any, 9001);
}

bool ServeurSynergie::Arreter()
{
    if (m_Ecouteur->isListening()) {
        m_Ecouteur->close();
        return true;
    }
    return false;
}

void ServeurSynergie::slNouveauClient()
{
    // pogne le nouveau client
    Client* client = new Client(m_Ecouteur->nextPendingConnection());
    m_Clients.insert(m_ID, client);
    m_ID++;
}
