#include "connexion.h"
#include <QMutex>
#include "Paquets/paquetchangernom.h"

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
    m_MangePaquets = new MangePaquetClient(this);

    connect (m_Socket, SIGNAL(readyRead()), this, SLOT(slPretALire()));
}

bool Connexion::Connecter(QString addr, int port)
{
    m_Socket->connectToHost(addr, port);
    return m_Socket->waitForConnected(1000);
}

void Connexion::ChangerNom(QString nom)
{
    EnvoyerPaquet(new PaquetChangerNom(nom));
}

void Connexion::slPretALire()
{
    LirePaquet();
}

void Connexion::LirePaquet()
{
    QByteArray bufferTaille;
    QDataStream streamTaille(&bufferTaille, QIODevice::ReadOnly);

    int taille = 0;
    bufferTaille = m_Socket->read(4);
    streamTaille >> taille;

    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadOnly);

    buffer = m_Socket->read(taille);

    m_MangePaquets->Interpreter(&stream);

    if (m_Socket->bytesAvailable() > 0) {
        LirePaquet();
    }
}

void Connexion::EnvoyerPaquet(BasePaquet* paquet)
{
    m_Socket->write(paquet->getBuffer());
}

MangePaquetClient* Connexion::getMangePaquets()
{
    return m_MangePaquets;
}


