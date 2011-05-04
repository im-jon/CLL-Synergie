#include "serveursynergie.h"
#include "Console/console.h"
#include "Reseau/Paquets/paquetenvoicollegues.h"
#include <QDir>

ServeurSynergie* ServeurSynergie::m_Instance = 0;

// Fonction pour le Singleton.
ServeurSynergie* ServeurSynergie::getInstance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
            m_Instance = new ServeurSynergie;
        mutex.unlock();
    }

    return m_Instance;
}

ServeurSynergie::ServeurSynergie(QObject *parent) :
    QObject(parent)
{
    m_GenerateurID = 1;
    m_Ecouteur = new QTcpServer(this);
    m_Clients = new QMap<int, Client*>();
    m_MangePaquets = new MangePaquetsServeur(this);

    connect (m_Ecouteur, SIGNAL(newConnection()), this, SLOT(slNouveauClient()));

    QDir dossierProjets("Projets");
    if (dossierProjets.exists()) {
        if (dossierProjets.entryList(QDir::AllDirs).count() == 2) {
            Console::getInstance()->Imprimer("Le répertoire de projets est vide");
        }
    } else {
        QDir().mkdir("Projets");
    }

    m_Projet = "Projet1";
    InitialiserFichiers();
}

bool ServeurSynergie::Demarrer()
{
    if (m_Ecouteur->listen(QHostAddress::Any, 9001)) {
        Console::getInstance()->Imprimer("Le serveur est en ligne");
        return true;
    }
    Console::getInstance()->Imprimer("Le serveur est incapable de se connecter");
    return false;
}

bool ServeurSynergie::Arreter()
{
    if (m_Ecouteur->isListening()) {
        m_Ecouteur->close();
        Console::getInstance()->Imprimer("Le serveur est hors ligne");
        return true;
    }
    Console::getInstance()->Imprimer("Le serveur est incapable de se déconnecter");
    return false;
}

void ServeurSynergie::slNouveauClient()
{
    Client* client = new Client(m_GenerateurID, m_Ecouteur->nextPendingConnection());
    AjouterClient(client);
    Console::getInstance()->Imprimer(client->getIP() + " est en ligne");
}

bool ServeurSynergie::AjouterClient(Client *client)
{
    m_Clients->insert(m_GenerateurID, client);
    m_GenerateurID++;
}

bool ServeurSynergie::EnleverClient(Client *client)
{
    if (m_Clients->remove(client->getID()) >= 1) {
        return true;
    }
    return false;
}

bool ServeurSynergie::NouveauProjet(QString nom)
{
    QDir dossierProjets("Projets");
    if (!dossierProjets.exists()) {
        if (!QDir().mkdir("Projets")) {
            return false;
        }
    }
    return dossierProjets.mkdir(nom);
}

void ServeurSynergie::InitialiserFichiers()
{
    m_Fichiers = new QMap<int, Fichier*>();
    QString fichier;

    int i = 0;
    foreach (fichier, QDir("Projets/" + m_Projet).entryList(QDir::NoDotAndDotDot | QDir::AllEntries)) {
        m_Fichiers->insert(i, new Fichier(i, fichier, this));
        i++;
    }
}

Fichier* ServeurSynergie::ChercherFichierParID(int id)
{
    return m_Fichiers->value(id);
}

QMap<int, Fichier*>* ServeurSynergie::getFichiers()
{
    return m_Fichiers;
}

MangePaquetsServeur* ServeurSynergie::getMangePaquets()
{
    return m_MangePaquets;
}

QMap<int, Client*>* ServeurSynergie::getClients()
{
    return m_Clients;
}

QString ServeurSynergie::getProjet()
{
    return m_Projet + "/";
}
