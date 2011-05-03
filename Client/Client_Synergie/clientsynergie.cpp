#include "clientsynergie.h"
#include "Reseau/Paquets/paquetchangernom.h"

ClientSynergie* ClientSynergie::m_Instance = 0;

ClientSynergie* ClientSynergie::getInstance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
            m_Instance = new ClientSynergie;
        mutex.unlock();
    }

    return m_Instance;
}

ClientSynergie::ClientSynergie(QObject *parent) :
    QObject(parent)
{
    m_Connexion = new Connexion(this);
    m_Fichiers = new QMap<QString, int>;
}

bool ClientSynergie::Connecter(QString adresse, int port)
{
    return m_Connexion->Connecter(adresse, port);
}

void ClientSynergie::AjouterFichier(QString nom, int id)
{
    m_Fichiers->insert(nom, id);
}

int ClientSynergie::TrouverFichierParNom(QString nom)
{
    return m_Fichiers->value(nom);
}

QString ClientSynergie::TrouverFichierParID(int id)
{
    return m_Fichiers->key(id);
}

void ClientSynergie::ChangerNom(QString nom)
{
    m_Nom = nom;

    m_Connexion->EnvoyerPaquet(new PaquetChangerNom(nom));
}

Connexion* ClientSynergie::getConnexion()
{
    return m_Connexion;
}

MangePaquetClient* ClientSynergie::getMangePaquets()
{
    return m_Connexion->getMangePaquets();
}
