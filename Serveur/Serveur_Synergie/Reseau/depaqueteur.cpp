#include "depaqueteur.h"
#include <QDataStream>
#include "Console/console.h"
#include "Paquets/paquetenvoicollegues.h"
#include "Paquets/paquetlistefichiers.h"
#include "Paquets/paquetouverturefichier.h"
#include "Paquets/paquetdonnees.h"
#include "Paquets/paquetinsertiontexte.h"
#include "Paquets/paquetconnexioncollegue.h"
#include "serveur.h"
#include "fichier.h"

Depaqueteur::Depaqueteur(QObject* parent) :
    QObject(parent)
{
}

void Depaqueteur::Interpreter(Client* client, QDataStream& stream)
{
    quint8 id;

    stream >> id;

    switch (id)
    {
        case 1:
            Reception_ChangerNom(client, stream);
            break;
        case 2:
            Reception_InsertionTexte(client, stream);
            break;
        case 4:
            Reception_EffacementTexte(client, stream);
            break;
        case 7:
            Reception_OuvrirFichier(client, stream);
            break;
        case 8:
            Reception_MauvaiseReponse(client, stream);
            break;
        case 10:
            Reception_DonneesRecues(client, stream);
            break;
        case 11:
            Reception_MessageChat(client, stream);
            break;
        case 12:
            Reception_FermerFichier(client, stream);
            break;
        default:
            Console::Instance()->Imprimer("Réception d'un paquet inconnu #" + QString::number(id));
            break;
    }
}

void Depaqueteur::Reception_ChangerNom(Client* client, QDataStream& stream)
{
    QString nom;

    stream >> nom;

    client->setNom(nom);

    client->EnvoyerPaquet(new PaquetEnvoiCollegues());
    client->EnvoyerPaquet(new PaquetListeFichiers());
    Serveur::Instance()->getClients()->EnvoyerPaquetATous(new PaquetConnexionCollegue(client), client);
}

void Depaqueteur::Reception_InsertionTexte(Client* client, QDataStream& stream)
{
    int id;
    int position;
    QString texte;

    stream >> id;
    stream >> position;
    stream >> texte;

    Fichier* fichier = Serveur::Instance()->getProjet()->getFichier(id);
    fichier->InsererTexte(texte, position, client);

}

void Depaqueteur::Reception_EffacementTexte(Client* client, QDataStream& stream)
{
    int id;
    int position;
    int longeur;

    stream >> id;
    stream >> position;
    stream >> longeur;

    Fichier* fichier = Serveur::Instance()->getProjet()->getFichier(id);
    fichier->EffacerTexte(position, longeur, client);
}

void Depaqueteur::Reception_OuvrirFichier(Client* client, QDataStream& stream)
{
    int id;

    stream >> id;

    client->OuvrirFichier(Serveur::Instance()->getProjet()->getFichier(id));
}

void Depaqueteur::Reception_DonneesRecues(Client* client, QDataStream& stream)
{
    int id;

    stream >> id;

    Transfer* transfer = client->getTransfer(id);
    if (transfer)
    {
        client->EnvoyerPaquet(new PaquetDonnees(transfer));
    }
}

void Depaqueteur::Reception_MessageChat(Client *client, QDataStream &stream)
{
    QString message;

    stream >> message;

    Serveur::Instance()->getChat()->NouveauMessage(client, message);
}

void Depaqueteur::Reception_MauvaiseReponse(Client *client, QDataStream &stream)
{
    int id;
    Fichier* fichier;

    stream >> id;

    fichier = Serveur::Instance()->getProjet()->getFichier(id);

    Serveur::Instance()->getVerificateur()->MauvaiseReponse(client, fichier);
}

void Depaqueteur::Reception_FermerFichier(Client *client, QDataStream &stream)
{
    int id;
    Fichier* fichier;

    stream >> id;

    fichier = Serveur::Instance()->getProjet()->getFichier(id);
    client->FermerFichier(fichier);
}
