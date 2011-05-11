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

    // On va dépaqueter le paquet que nous venons de lire.
    Serveur::Instance()->getDepaqueteur()->Depaqueter(m_Client, stream);

    // Au cas ou des données ont été reçues entre-temps, on ne vas pas attendre que slPretALire soit invoqué.
    if (m_Socket->bytesAvailable() > 0)
    {
        Lire();
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
