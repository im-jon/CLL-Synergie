#ifndef DEPAQUETEUR_H
#define DEPAQUETEUR_H

#include <QObject>
#include "client.h"

class Depaqueteur : public QObject
{
    Q_OBJECT
public:
    explicit Depaqueteur(QObject* parent = 0);
    void Interpreter(Client* client, QDataStream& stream);

private:
    void Reception_ChangerNom(Client* client, QDataStream& stream);
    void Reception_OuvrirFichier(Client* client, QDataStream& stream);
    void Reception_DonneesRecues(Client* client, QDataStream& stream);
    void Reception_InsertionTexte(Client* client, QDataStream& stream);
    void Reception_EffacementTexte(Client* client, QDataStream& stream);
    void Reception_MessageChat(Client* client, QDataStream& stream);
    void Reception_MauvaiseReponse(Client* client, QDataStream& stream);
    void Reception_FermerFichier(Client* client, QDataStream& stream);

signals:

public slots:

};

#endif // DEPAQUETEUR_H
