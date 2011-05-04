#ifndef FICHIER_H
#define FICHIER_H

#include <QObject>
#include <QList>
#include <QFile>
#include "Reseau/client.h"

class Client;

class Fichier : public QObject
{
    Q_OBJECT
public:
    explicit Fichier(int id, QString chemin, QObject *parent = 0);

    void Sauvegarder();
    void AjouterClient(Client* client);
    void EnleverClient(Client* client);
    void InsererTexte(QString texte, int position, Client* auteur = 0);
    QString getChemin();
    QString* getContenu();
    QList<Client*>* getClients();
    int getID();

private:
    void ChargerContenu();
    void DechargerContenu();

    bool m_Charge; // Chargé
    QFile* m_Fichier;
    QString m_Chemin;
    QString m_Contenu;
    QList<Client*>* m_Clients;
    int m_ID;

signals:

public slots:

};

#endif // FICHIER_H
