#include "connexion.h"
#include <QMutex>
#include "Paquets/paquetchangernom.h"

Connexion::Connexion(QObject *parent) :
    QObject(parent)
{
    m_Socket = new QTcpSocket(this);
    m_Depaqueteur = new Depaqueteur(this);

    connect (m_Socket, SIGNAL(readyRead()), this, SLOT(slPretALire()));
}

bool Connexion::Connecter(QString addr, int port)
{
    m_Socket->connectToHost(addr, port);
    return m_Socket->waitForConnected(1000);
}

void Connexion::LirePaquet()
{
    int taille;
    memcpy(&taille, m_Socket->read(sizeof(taille)), sizeof(taille));

    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadOnly);

    buffer = m_Socket->read(taille);

    m_Depaqueteur->Interpreter(stream);

    if (m_Socket->bytesAvailable() > 0)
    {
        LirePaquet();
    }
}

void Connexion::EnvoyerPaquet(BasePaquet* paquet)
{
    m_Socket->write(paquet->getBuffer());
}

Depaqueteur* Connexion::getDepaqueteur()
{
    return m_Depaqueteur;
}

void Connexion::slPretALire()
{
    LirePaquet();
}


