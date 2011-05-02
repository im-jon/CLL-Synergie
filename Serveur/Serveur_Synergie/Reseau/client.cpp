#include "client.h"
#include <QByteArray>
#include <QDataStream>
#include <QtCore>
#include "serveursynergie.h"
#include "Console/console.h"
#include "Paquets/basepaquetserveur.h"

Client::Client(int id, QTcpSocket* socket)
{
    m_ID = id;
    m_Socket = socket;

    connect(m_Socket, SIGNAL(readyRead()),this,SLOT(slPretALire()));
    connect(m_Socket,SIGNAL(disconnected()),this,SLOT(slOnDeconnection())); // Parenthèses ???
}

void Client::EnvoyerPaquet(BasePaquetServeur* paquet)
{
   m_Socket->write(paquet->getBuffer());
   m_Socket->waitForBytesWritten();
}

void Client::slPretALire()
{
    LirePaquet();
}

void Client::LirePaquet()
{
    QByteArray bufferTaille;
    QDataStream streamTaille(&bufferTaille, QIODevice::ReadOnly);

    int taille = 0;
    bufferTaille = m_Socket->read(4);
    streamTaille >> taille;

    QByteArray buffer;
    QDataStream stream(&buffer, QIODevice::ReadOnly);

    buffer = m_Socket->read(taille);

    ServeurSynergie::getInstance()->getMangePaquets()->Interpreter(this, &stream);

    if (m_Socket->bytesAvailable() > 0) {
        LirePaquet();
    }
}

void Client::slOnDeconnection()
{
    m_Socket->close();
    ServeurSynergie::getInstance()->EnleverClient(this);
    Console::getInstance()->Imprimer(m_Nom + " est déconnecté");
}

QString Client::getNom()
{
    return m_Nom;
}

int Client::getID()
{
    return m_ID;
}

QString Client::getIP()
{
    return m_Socket->peerAddress().toString();
}

void Client::setNom(QString nom)
{
    m_Nom = nom;
    Console::getInstance()->Imprimer(getIP() + " change de nom pour " + nom);
}
