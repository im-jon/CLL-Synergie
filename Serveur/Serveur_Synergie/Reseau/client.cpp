#include "client.h"
#include <QByteArray>
#include <QDataStream>
#include <QtCore>
#include "serveursynergie.h"
#include "Console/console.h"
#include "Paquets/paquetouverturefichier.h"
#include "Paquets/basepaquetserveur.h"
#include "Paquets/paquetdonnees.h"
#include "Paquets/paquetdeconnexioncollegue.h"

int Client::GenerateurID = 1;

Client::Client(QTcpSocket* socket, QObject* parent) :
    QObject(parent)
{
    m_ID = GenerateurID;
    m_Socket = socket;
    m_Transfers = new QMap<int, Transfer*>;
    m_FichiersOuverts = new QList<Fichier*>;

    connect(m_Socket, SIGNAL(readyRead()), this, SLOT(slPretALire()));
    connect(m_Socket, SIGNAL(disconnected()), this, SLOT(slDeconnection()));

    GenerateurID++;
}

void Client::EnvoyerPaquet(BasePaquetServeur* paquet)
{
   m_Socket->write(paquet->getBuffer());
   m_Socket->waitForBytesWritten();
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

    ServeurSynergie::getInstance()->getMangePaquets()->Interpreter(this, stream);

    if (m_Socket->bytesAvailable() > 0)
    {
        LirePaquet();
    }
}

void Client::Deconnecter()
{
    m_Socket->close();

    Fichier* fichier;
    foreach (fichier, *m_FichiersOuverts)
    {
        FermerFichier(fichier);
    }

    ServeurSynergie::getInstance()->EnleverClient(this);
    ServeurSynergie::getInstance()->EnvoyerPaquetATous(new PaquetDeconnexionCollegue(this));

    Console::getInstance()->Imprimer(m_Nom + " est déconnecté");
}

void Client::OuvrirFichier(Fichier* fichier)
{
    fichier->AjouterClient(this);
    m_FichiersOuverts->append(fichier);
    EnvoyerFichier(fichier);
}

void Client::FermerFichier(Fichier *fichier)
{
    fichier->EnleverClient(this);
    m_FichiersOuverts->removeOne(fichier);
}

void Client::EnvoyerFichier(Fichier* fichier)
{
    Transfer* transfer = new Transfer(fichier, this);
    m_Transfers->insert(fichier->getID(), transfer);

    connect (transfer, SIGNAL(siFin(int)), this, SLOT(slFinTransfer(int)));

    EnvoyerPaquet(new PaquetOuvertureFichier(fichier));
    EnvoyerPaquet(new PaquetDonnees(transfer));
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

Transfer* Client::getTransfer(int id)
{
    return m_Transfers->value(id);
}

void Client::setNom(QString nom)
{
    m_Nom = nom;
    Console::getInstance()->Imprimer(getIP() + " change de nom pour " + nom);
}

QList<Fichier*>* Client::getFichiers()
{
    return m_FichiersOuverts;
}

void Client::slPretALire()
{
    LirePaquet();
}

void Client::slDeconnection()
{
    Deconnecter();
}

void Client::slFinTransfer(int id)
{
    m_Transfers->remove(id);
}
