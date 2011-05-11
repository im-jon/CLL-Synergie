#include "connexion.h"
#include "serveur.h"
#include "depaqueteur.h"

Connexion::Connexion(QTcpSocket* socket, Client* client) :
    QObject(client)
{
    m_Socket = socket;
    m_Client = client;

    connect(m_Socket, SIGNAL(readyRead()), this, SLOT(slPretALire()));
    connect(m_Socket, SIGNAL(disconnected()), this, SLOT(slDeconnexion()));
}

void Connexion::Lire()
{
    int taille;
    memcpy(&taille, m_Socket->read(sizeof(taille)), sizeof(taille));

    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadOnly);

    buffer = m_Socket->read(taille);

    Serveur::Instance()->getDepaqueteur()->Interpreter(m_Client, stream);

    if (m_Socket->bytesAvailable() > 0)
    {
        Lire();
    }
}

void Connexion::Envoyer(BasePaquet* paquet)
{
   m_Socket->waitForBytesWritten();
   m_Socket->write(paquet->getBuffer());
   m_Socket->waitForBytesWritten();
}

void Connexion::EnvoyerBytes(QByteArray donnees)
{
    m_Socket->write(donnees);
    m_Socket->waitForBytesWritten();
}

void Connexion::Fermer()
{
    m_Socket->close();
}

QString Connexion::getIP()
{
    return m_Socket->peerAddress().toString();
}


void Connexion::slPretALire()
{
    Lire();
}

void Connexion::slDeconnexion()
{
    m_Client->Deconnecter();
}
