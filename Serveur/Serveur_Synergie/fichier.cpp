#include "fichier.h"
#include "serveur.h"
#include <QTextOStream>
#include "Console/console.h"
#include "Reseau/Paquets/paquetinsertiontexte.h"
#include "Reseau/Paquets/paqueteffacementtexte.h"
#include "Reseau/Paquets/paquetouvrirfeuille.h"
#include "Reseau/Paquets/paquetfermerfeuille.h"
#include "serveur.h"
#include "curseur.h"

const int Seuil = 100;

int Fichier::GenerateurID = 0;

Fichier::Fichier(QString chemin, QObject *parent) :
    QObject(parent)
{
    m_ID = GenerateurID;
    m_Chemin = chemin;
    m_Clients = new QList<Client*>;
    m_Curseurs = new QMap<Client*, Curseur*>;
    m_Charge = false;

    GenerateurID++;
}

void Fichier::Fermer()
{
    Sauvegarder();
    DechargerContenu();
}

void Fichier::Sauvegarder()
{
        m_Fichier->open(QFile::WriteOnly | QFile::Truncate);
        QTextStream stream(m_Fichier);
        stream << m_Contenu;
        m_Fichier->close();
        m_Modifications = 0;
}

void Fichier::ChargerContenu()
{
    if (!m_Charge)
    {
        m_Fichier = new QFile(Serveur::Instance()->getProjet()->getChemin() + m_Chemin); // Corriger ici
        m_Fichier->open(QFile::ReadWrite);
        QTextStream* stream = new QTextStream(m_Fichier);
        m_Contenu = stream->readAll();
        m_Fichier->close();
        m_Charge = true;
    }
}

void Fichier::DechargerContenu()
{
    if (m_Charge)
    {
        m_Fichier->close();
        m_Contenu = QString::null;
        m_Charge = false;
    }
}

void Fichier::AjouterClient(Client *client)
{
    if (m_Clients->count() == 0)
    {
        ChargerContenu();
    }

    m_Clients->append(client);
    m_Curseurs->insert(client, new Curseur(client));

    Clients::EnvoyerPaquetAListe(
                m_Clients,
                new PaquetOuvrirFeuille(client, this),
                client);
}

void Fichier::EnleverClient(Client *client)
{
    m_Clients->removeOne(client);
    m_Curseurs->remove(client);

    if (m_Clients->count() == 0)
    {
        Fermer();
    }
    else
    {
        Clients::EnvoyerPaquetAListe(
                    m_Clients,
                    new PaquetFermerFeuille(client, this),
                    client);
    }
}

void Fichier::InsererTexte(QString texte, int position, Client* auteur)
{
    m_Contenu.insert(position, texte);
    Clients::EnvoyerPaquetAListe(
                m_Clients,
                new PaquetInsertionTexte(auteur, this, texte, position),
                auteur);

    getCurseur(auteur)->setPosition(position + texte.length());
    NouvelleModification();
}

void Fichier::EffacerTexte(int position, int longeur, Client *auteur)
{
    m_Contenu = m_Contenu.remove(position, longeur);

    Clients::EnvoyerPaquetAListe(
                m_Clients,
                new PaquetEffacementTexte(auteur, this, position, longeur),
                auteur);

    getCurseur(auteur)->setPosition(position - longeur);
    NouvelleModification();
}

void Fichier::NouvelleModification()
{
    m_Modifications++;

    if (m_Modifications >= Seuil)
    {
        Sauvegarder();
    }
}

QString Fichier::getChemin()
{
    return m_Chemin;
}

int Fichier::getID()
{
    return m_ID;
}

QString* Fichier::getContenu()
{
    return &m_Contenu;
}

QList<Client*>* Fichier::getClients()
{
    return m_Clients;
}

Curseur* Fichier::getCurseur(Client* client)
{
    return m_Curseurs->value(client);
}

int Fichier::longeur()
{
    return m_Contenu.length();
}

int Fichier::nombreClients()
{
    return m_Clients->count();
}

bool Fichier::charge()
{
    return m_Charge;
}
