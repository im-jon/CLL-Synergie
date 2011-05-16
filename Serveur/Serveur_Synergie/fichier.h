#ifndef FICHIER_H
#define FICHIER_H

#include <QObject>
#include <QList>
#include <QFile>
#include "client.h"
#include "curseur.h"

class Client;
class Curseur;

class Fichier : public QObject
{
    Q_OBJECT
public:
    explicit Fichier(QString chemin, QObject *parent = 0);

    void Fermer();
    void Sauvegarder();
    void AjouterClient(Client* client);
    void EnleverClient(Client* client);
    void InsererTexte(QString texte, int position, Client* auteur = 0);
    void EffacerTexte(int position, int longeur, Client* auteur = 0);
    void ChangerLigneCurseur(Client* client, int ligne);
    QString getChemin();
    QString* getContenu();
    QList<Client*>* getClients();
    int getID();
    int longeur();
    int nombreClients();
    Curseur* getCurseur(Client* client);

private:
    static int GenerateurID;

    void ChargerContenu();
    void DechargerContenu();
    void NouvelleModification();

    bool m_Charge;
    QFile* m_Fichier;
    QString m_Chemin;
    QString m_Contenu;
    QList<Client*>* m_Clients;
    QMap<Client*, Curseur*>* m_Curseurs;
    int m_ID;
    int m_Modifications;

signals:

public slots:

};

#endif // FICHIER_H
