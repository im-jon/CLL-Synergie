#include "serveur.h"
#include "Console/console.h"
#include "clients.h"
#include "Reseau/Paquets/paquetenvoicollegues.h"
#include "Reseau/Paquets/paquetconnexioncollegue.h"
#include <QDir>
#include <QMapIterator>

Serveur* Serveur::m_Instance = 0;

Serveur::Serveur(QObject* parent) :
    QObject(parent)
{
    m_Chat = new Chat(this);
    m_Clients = new Clients(this);
    m_Ecouteur = new QTcpServer(this);
    m_Depaqueteur = new Depaqueteur(this);
    m_Verificateur = new Verificateur(this);

    connect (m_Ecouteur, SIGNAL(newConnection()), this, SLOT(slNouveauClient()));

    m_Projet = new Projet("Projet1", this);
    m_Projet->Creer();
    m_Projet->Ouvrir();
}

bool Serveur::Demarrer()
{
    if (m_Ecouteur->listen(QHostAddress::Any, 9001))
    {
        m_Verificateur->Demarrer();
        m_Chat->Demarrer();

        Console::Instance()->Imprimer("Le serveur est en ligne");
        return true;
    }
    Console::Instance()->Imprimer("Le serveur est incapable de se connecter");
    return false;
}

bool Serveur::Arreter()
{
    if (m_Ecouteur->isListening())
    {
        m_Ecouteur->close();

        m_Verificateur->Arreter();
        m_Chat->Arreter();

        Console::Instance()->Imprimer("Le serveur est hors ligne");
        return true;
    }

    m_Projet->Fermer();

    Console::Instance()->Imprimer("Le serveur est incapable de se déconnecter");
    return false;
}

Depaqueteur* Serveur::getDepaqueteur()
{
    return m_Depaqueteur;
}

Projet* Serveur::getProjet()
{
    return m_Projet;
}

Clients* Serveur::getClients()
{
    return m_Clients;
}

Verificateur* Serveur::getVerificateur()
{
    return m_Verificateur;
}

Chat* Serveur::getChat()
{
    return m_Chat;
}

void Serveur::slNouveauClient()
{
    Client* client = new Client(m_Ecouteur->nextPendingConnection(), this);
    m_Clients->AjouterClient(client);

    Console::Instance()->Imprimer(client->getConnexion()->getIP() + " est en ligne");
}

// Fonction pour le Singleton.
Serveur* Serveur::Instance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
        {
            m_Instance = new Serveur;
        }
        mutex.unlock();
    }

    return m_Instance;
}
