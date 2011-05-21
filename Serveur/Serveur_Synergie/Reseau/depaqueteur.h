#ifndef DEPAQUETEUR_H
#define DEPAQUETEUR_H

#include <QObject>
#include <QColor>

#include "client.h"

// Le but principal du dépaqueteur est de lire et interprèter chacun des paquets
// qu'un client peut envoyer au serveur.
// Nous utilisons un QDataStream pour faciliter la lecture des données.

class Depaqueteur : public QObject
{
    Q_OBJECT
public:
    explicit Depaqueteur(QObject* parent = 0);
    void Depaqueter(Client* client, QDataStream& stream);

// Chaque paquet venant du client est interprété dans une fonction de réception
private:
    void Reception_Authentification(Client* client, QDataStream& stream);
    void Reception_OuvrirFichier(Client* client, QDataStream& stream);
    void Reception_DonneesRecues(Client* client, QDataStream& stream);
    void Reception_InsertionTexte(Client* client, QDataStream& stream);
    void Reception_EffacementTexte(Client* client, QDataStream& stream);
    void Reception_MessageChat(Client* client, QDataStream& stream);
    void Reception_ReponseVerification(Client* client, QDataStream& stream);
    void Reception_FermerFichier(Client* client, QDataStream& stream);
};

#endif // DEPAQUETEUR_H
