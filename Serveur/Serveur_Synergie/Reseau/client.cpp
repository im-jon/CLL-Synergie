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
}

void Client::slPretALire()
{
    QByteArray buffer;
    buffer = m_Socket->readAll();
    QDataStream stream(&buffer, QIODevice::ReadOnly);

    ServeurSynergie::getInstance()->getMangePaquets()->Interpreter(this, &stream);
}

void Client::slOnDeconnection()
{
    m_Socket->close();
    ServeurSynergie::getInstance()->EnleverClient(this);
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
    Console::getInstance()->Imprimer(m_Socket->peerAddress().toString() + " change de nom pour " + nom);
}
