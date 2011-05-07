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
    static int getGenerateurID();
    explicit Fichier(QString chemin, QObject *parent = 0);

    void Fermer();
    void Sauvegarder();
    void AjouterClient(Client* client);
    void EnleverClient(Client* client);
    void InsererTexte(QString texte, int position, Client* auteur = 0);
    void EffacerTexte(int position, int longeur, Client* auteur = 0);
    QString getChemin();
    QString* getContenu();
    QList<Client*>* getClients();
    int getID();

private:
    static int GenerateurID;
    void ChargerContenu();
    void DechargerContenu();
    void NouvelleModification();

    bool m_Charge; // Chargé
    QFile* m_Fichier;
    QString m_Chemin;
    QString m_Contenu;
    QList<Client*>* m_Clients;
    int m_ID;
    int m_Modifications;

signals:

public slots:

};

#endif // FICHIER_H
