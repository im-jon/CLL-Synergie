#include "clientsynergie.h"
#include "Reseau/Paquets/paquetauthentification.h"
#include "Reseau/Paquets/paquetinsertiontexte.h"
#include "Reseau/Paquets/paqueteffacementtexte.h"
#include "Reseau/Paquets/paquetenvoichat.h"
#include "Reseau/Paquets/paquetreponseverification.h"
#include "Reseau/Paquets/paquetfermerfeuille.h"
#include "Reseau/Paquets/paquetlignechangee.h"

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

void ClientSynergie::Authentifier()
{
    m_Connexion->EnvoyerPaquet(new PaquetAuthentification(m_Nom, m_Couleur));
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

QColor ClientSynergie::getCouleur()
{
    return m_Couleur;
}

void ClientSynergie::setNom(QString nom)
{
    m_Nom = nom;
}

void ClientSynergie::setCouleur(QColor couleur)
{
    m_Couleur = couleur;
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

//Slots reliées a l'interface graphique
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

void ClientSynergie::slVerification(int id, bool reponse)
{
    m_Connexion->EnvoyerPaquet(new PaquetReponseVerification(id, reponse));
}

void ClientSynergie::slFermerFichier(int id)
{
    m_Connexion->EnvoyerPaquet(new PaquetFermerFeuille(id));
}

void ClientSynergie::slLigneChangee(int feuille, int ligne)
{
    m_Connexion->EnvoyerPaquet(new PaquetLigneChangee(feuille, ligne));
}

//Instance
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
