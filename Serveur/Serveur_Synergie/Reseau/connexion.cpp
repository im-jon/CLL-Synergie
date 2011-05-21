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
    while (m_Socket->bytesAvailable() > 0)
    {
        int taille;
        QByteArray buffer;

        // Nous utilisons la fonction 'memcpy' car il est trop tôt pour utiliser
        // un QDataStream. Nous sommes également très limité lorsqu'il est
        // question de convertir des bytes en entier
        memcpy(&taille, m_Socket->read(sizeof(taille)), sizeof(taille));

        QDataStream stream(&buffer, QIODevice::ReadOnly);

        buffer = m_Socket->read(taille);

        // Nous utilisons le dépaqueteur pour lire notre paquet
        Serveur::Instance()->getDepaqueteur()->Depaqueter(m_Client, stream);
    }
}

void Connexion::EnvoyerPaquet(BasePaquet* paquet)
{
    EnvoyerBytes(paquet->getBuffer());
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
