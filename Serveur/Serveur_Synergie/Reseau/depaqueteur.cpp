#include <QDataStream>

#include "depaqueteur.h"
#include "serveur.h"
#include "fichier.h"

#include "Console/console.h"

#include "Paquets/paquetouverturefichier.h"
#include "Paquets/paquetdonnees.h"
#include "Paquets/paquetinsertiontexte.h"
#include "Paquets/paquetmessagechat.h"

Depaqueteur::Depaqueteur(QObject* parent) :
    QObject(parent)
{

}

void Depaqueteur::Depaqueter(Client* client, QDataStream& stream)
{
    quint8 id;

    stream >> id;

    switch (id)
    {
        case 1:
            Reception_Authentification(client, stream);
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
            Reception_ReponseVerification(client, stream);
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
            // TODO: déconnecter le client si on reçoit un mauvais paquet par mesure de sécurité
            Console::Instance()->Imprimer("Réception d'un paquet inconnu #" + QString::number(id));
            break;
    }
}

// Le client veut s'authentifier
void Depaqueteur::Reception_Authentification(Client* client, QDataStream& stream)
{
    QString nom;
    QColor couleur;

    stream >> nom;
    stream >> couleur;

    client->Authentifier(nom, couleur);
}


// Le client veut insérer du texte dans un fichier
void Depaqueteur::Reception_InsertionTexte(Client* client, QDataStream& stream)
{
    int id;
    int position;
    QString texte;
    Fichier* fichier;

    stream >> id;
    stream >> position;
    stream >> texte;

    fichier = Serveur::Instance()->getProjet()->getFichier(id);
    fichier->InsererTexte(texte, position, client);

}

// Le client veut effacer du texte dans un fichier
void Depaqueteur::Reception_EffacementTexte(Client* client, QDataStream& stream)
{
    int id;
    int position;
    int longeur;
    Fichier* fichier;

    stream >> id;
    stream >> position;
    stream >> longeur;

    fichier = Serveur::Instance()->getProjet()->getFichier(id);
    fichier->EffacerTexte(position, longeur, client);
}

// Le client veut ouvrir un fichier
void Depaqueteur::Reception_OuvrirFichier(Client* client, QDataStream& stream)
{
    int id;
    Fichier* fichier;

    stream >> id;

    fichier = Serveur::Instance()->getProjet()->getFichier(id);
    client->OuvrirFichier(fichier);
}

// Le client ferme un fichier
void Depaqueteur::Reception_FermerFichier(Client *client, QDataStream &stream)
{
    int id;
    Fichier* fichier;

    stream >> id;

    fichier = Serveur::Instance()->getProjet()->getFichier(id);
    client->FermerFichier(fichier);
}

// Le client confirme la réception d'un bloc de texte (voir 'Transfer')
void Depaqueteur::Reception_DonneesRecues(Client* client, QDataStream& stream)
{
    int id;
    Transfer* transfer;

    stream >> id;

    // Nous allons chercher le transfer en question. Si le dernier bloc de texte
    // à été envoyé, la fonction retournera un pointeur nul. C'est donc ici que
    // la boucle de transfer se termine
    transfer = client->getTransfer(id);
    if (transfer)
    {
        client->EnvoyerPaquet(new PaquetDonnees(transfer));
    }
}

// Le client à envoyé un message sur le chat
void Depaqueteur::Reception_MessageChat(Client *client, QDataStream &stream)
{
    Message* message;
    QString contenu;

    stream >> contenu;

    message = new Message(client, contenu, this);

    Serveur::Instance()->getChat()->NouveauMessage(message);
}

// Le client réponds à la vérification de synchronisation (voir 'Verificateur')
void Depaqueteur::Reception_ReponseVerification(Client *client, QDataStream &stream)
{
    int id;
    bool reponse;
    Fichier* fichier;

    stream >> id;
    stream >> reponse;

    fichier = Serveur::Instance()->getProjet()->getFichier(id);
    Serveur::Instance()->getVerificateur()->ReceptionReponse(reponse, client, fichier);
}
