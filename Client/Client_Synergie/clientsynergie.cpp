#include "clientsynergie.h"
#include "Reseau/Paquets/paquetchangernom.h"
#include "Reseau/Paquets/paquetinsertiontexte.h"
#include "Reseau/Paquets/paqueteffacementtexte.h"
#include "Reseau/Paquets/paquetenvoichat.h"
#include "Reseau/Paquets/paquetmauvaisesynchro.h"
#include "Reseau/Paquets/paquetfermerfichier.h"

ClientSynergie* ClientSynergie::m_Instance = 0;

ClientSynergie::ClientSynergie(QObject *parent) :
    QObject(parent)
{
    m_Connexion = new Connexion(this);
    m_Chat = new Chat(this);
    m_Feuilles = new QMap<int, Feuille*>;
    m_Collegues = new QMap<int, Collegue*>;
}

bool ClientSynergie::Connecter(QString adresse, int port)
{
    return m_Connexion->Connecter(adresse, port);
}

void ClientSynergie::AjouterFeuille(QString nom, int id)
{
    Feuille* feuille = new Feuille(id, nom, this);
    m_Feuilles->insert(id, feuille);

    emit (siAjoutFeuille(feuille));
}

Feuille* ClientSynergie::getFeuille(int id)
{
    return m_Feuilles->value(id);
}

Collegue* ClientSynergie::getCollegue(int id)
{
    return m_Collegues->value(id);
}

void ClientSynergie::Renommer(QString nom)
{
    m_Nom = nom;

    m_Connexion->EnvoyerPaquet(new PaquetChangerNom(nom));
}

Connexion* ClientSynergie::getConnexion()
{
    return m_Connexion;
}

Chat* ClientSynergie::getChat()
{
    return m_Chat;
}

Depaqueteur* ClientSynergie::getDepaqueteur()
{
    return m_Connexion->getDepaqueteur();
}

QString ClientSynergie::getNom()
{
    return m_Nom;
}

void ClientSynergie::ConnexionCollegue(Collegue *collegue)
{
    m_Collegues->insert(collegue->getID(), collegue);

    emit (siConnexionCollegue(collegue));
}

void ClientSynergie::DeconnexionCollegue(int id)
{
    Collegue* collegue = m_Collegues->value(id);
    m_Collegues->remove(id);

    emit (siDeconnexionCollegue(collegue));
}

//Slots relier a l'interface graphique
void ClientSynergie::slInsertionTexte(int id, int pos, QString texte)
{
    m_Connexion->EnvoyerPaquet(new PaquetInsertionTexte(id, pos, texte));
}

void ClientSynergie::slEffacementTexte(int id, int pos, int longeur)
{
    m_Connexion->EnvoyerPaquet(new PaquetEffacementTexte(id, pos, longeur));
}

void ClientSynergie::slEnvoiTexteChat(QString Texte)
{
    m_Connexion->EnvoyerPaquet(new PaquetEnvoiChat(Texte));
}

void ClientSynergie::slMauvaiseSynchro(int id)
{
    m_Connexion->EnvoyerPaquet(new paquetMauvaiseSynchro(id));
}

void ClientSynergie::slFermerFichier(int id)
{
    m_Connexion->EnvoyerPaquet(new PaquetFermerFichier(id));
}

ClientSynergie* ClientSynergie::Instance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();

        if (!m_Instance)
        {
            m_Instance = new ClientSynergie;
        }
        mutex.unlock();
    }

    return m_Instance;
}
