#include "fichier.h"
#include "serveursynergie.h"
#include <QTextOStream>
#include "Console/console.h"
#include "Reseau/Paquets/paquetinsertiontexte.h"
#include "Reseau/Paquets/paqueteffacementtexte.h"
#include "serveursynergie.h"

const int Seuil = 100;

int Fichier::GenerateurID = 0;

Fichier::Fichier(QString chemin, QObject *parent) :
    QObject(parent)
{
    m_ID = GenerateurID;
    m_Chemin = chemin;
    m_Clients = new QList<Client*>();
    m_Charge = false;

    GenerateurID++;
}

void Fichier::Sauvegarder()
{
    if (m_Modifications > 0) {
        QTextStream stream(m_Fichier);
        stream << m_Contenu;
        m_Modifications = 0;
    }
}

void Fichier::ChargerContenu()
{
    if (!m_Charge) {
        m_Fichier = new QFile("Projets/" + ServeurSynergie::getInstance()->getProjet()->getNom() + "/" + m_Chemin); // Corriger ici
        m_Fichier->open(QFile::ReadWrite);
        QTextStream* stream = new QTextStream(m_Fichier);
        m_Contenu = stream->readAll();
        m_Charge = true;
        m_Fichier->close();
        m_Fichier->open(QFile::WriteOnly|QFile::Truncate);
    }
}

void Fichier::DechargerContenu()
{
    Sauvegarder();

    if (m_Charge) {
        m_Fichier->close();
        m_Contenu = QString::null;
        m_Charge = false;
    }
}

void Fichier::AjouterClient(Client *client)
{
    if (m_Clients->count() == 0) {
        ChargerContenu();
    }

    m_Clients->append(client);
}

void Fichier::EnleverClient(Client *client)
{
    m_Clients->removeOne(client);

    if (m_Clients->count() == 0) {
        DechargerContenu();
    }
}

void Fichier::InsererTexte(QString texte, int position, Client* auteur)
{
    m_Contenu.insert(position, texte);

    ServeurSynergie::getInstance()->EnvoyerPaquetAListe(
                m_Clients,
                new PaquetInsertionTexte(this, texte, position),
                auteur);

    NouvelleModification();
}

void Fichier::EffacerTexte(int position, int longeur, Client *auteur)
{
    m_Contenu = m_Contenu.remove(position, longeur);

    ServeurSynergie::getInstance()->EnvoyerPaquetAListe(
                m_Clients,
                new PaquetEffacementTexte(this, position, longeur),
                auteur);

    NouvelleModification();
}

void Fichier::NouvelleModification()
{
    m_Modifications++;
    if (m_Modifications >= Seuil) {
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

int Fichier::getGenerateurID()
{
    return GenerateurID;
}
