#include "connexion.h"
#include <QMutex>

Connexion* Connexion::m_Instance = 0;

Connexion* Connexion::getInstance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
            m_Instance = new Connexion;
        mutex.unlock();
    }

    return m_Instance;
}

Connexion::Connexion(QObject *parent) :
    QObject(parent)
{
    m_Socket = new QTcpSocket(this);
}

bool Connexion::Connecter(QString addr, int port)
{
    m_Socket->connectToHost(addr, port);
}


