#include "mangepaquets.h"
#include <QDataStream>
#include "Console/console.h"
#include "Paquets/paquetenvoicollegues.h"
#include "Paquets/paquetlistefichiers.h"
#include "Paquets/paquetouverturefichier.h"
#include "Paquets/paquetdonnees.h"
#include "Paquets/paquetinsertiontexte.h"
#include "Paquets/paquetconnexioncollegue.h"
#include "serveursynergie.h"
#include "fichier.h"

MangePaquets::MangePaquets(QObject* parent) :
    QObject(parent)
{
}

void MangePaquets::Interpreter(Client* client, QDataStream& stream)
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
        case 10:
            Reception_DonneesRecues(client, stream);
            break;
        default:
            Console::getInstance()->Imprimer("Réception d'un paquet inconnu #" + QString::number(id));
            break;
    }
}

void MangePaquets::Reception_ChangerNom(Client* client, QDataStream& stream)
{
    QString nom;

    stream >> nom;

    client->setNom(nom);

    client->EnvoyerPaquet(new PaquetEnvoiCollegues());
    client->EnvoyerPaquet(new PaquetListeFichiers());
    ServeurSynergie::getInstance()->EnvoyerPaquetATous(new PaquetConnexionCollegue(client), client);
}

void MangePaquets::Reception_InsertionTexte(Client* client, QDataStream& stream)
{
    int id;
    int position;
    QString texte;

    stream >> id;
    stream >> position;
    stream >> texte;

    Fichier* fichier = ServeurSynergie::getInstance()->getProjet()->getFichier(id);
    fichier->InsererTexte(texte, position, client);

}

void MangePaquets::Reception_EffacementTexte(Client* client, QDataStream& stream)
{
    int id;
    int position;
    int longeur;

    stream >> id;
    stream >> position;
    stream >> longeur;

    Fichier* fichier = ServeurSynergie::getInstance()->getProjet()->getFichier(id);
    fichier->EffacerTexte(position, longeur, client);
}

void MangePaquets::Reception_OuvrirFichier(Client* client, QDataStream& stream)
{
    int id;

    stream >> id;

    client->OuvrirFichier(ServeurSynergie::getInstance()->getProjet()->getFichier(id));
}

void MangePaquets::Reception_DonneesRecues(Client* client, QDataStream& stream)
{
    int id;

    stream >> id;

    Transfer* transfer = client->getTransfer(id);
    if (transfer)
    {
        client->EnvoyerPaquet(new PaquetDonnees(transfer));
    }
}
