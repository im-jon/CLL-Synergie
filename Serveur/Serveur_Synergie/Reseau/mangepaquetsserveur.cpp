#include "mangepaquetsserveur.h"
#include <QDataStream>
#include "Console/console.h"
#include "Paquets/paquetenvoicollegues.h"
#include "Paquets/paquetlistefichiers.h"
#include "Paquets/paquetouverturefichier.h"
#include "Paquets/paquetdonnees.h"

MangePaquetsServeur::MangePaquetsServeur(QObject *parent) :
    QObject(parent)
{
}

void MangePaquetsServeur::Interpreter(Client* client, QDataStream* stream)
{
    quint8 id;
    *stream >> id;

    switch (id) {
    case 1:
        Reception_ChangerNom(client, stream);
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

void MangePaquetsServeur::Reception_ChangerNom(Client* client, QDataStream* stream)
{
    QString nom;

    *stream >> nom;

    client->setNom(nom);

    client->EnvoyerPaquet(new PaquetEnvoiCollegues());
    client->EnvoyerPaquet(new PaquetListeFichiers());
}

void MangePaquetsServeur::Reception_OuvrirFichier(Client *client, QDataStream *stream)
{
    int id;

    *stream >> id;

    client->EnvoyerFeuille(id);
}

void MangePaquetsServeur::Reception_DonneesRecues(Client *client, QDataStream *stream)
{
    int id;
    *stream >> id;

    Transfer* transfer = client->getTransfer(id);
    if (!transfer->getFini()) {
        client->EnvoyerPaquet(new PaquetDonnees(id, transfer->LireBloc()));
    }
}
