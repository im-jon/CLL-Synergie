#ifndef SERVEURSYNERGIE_H
#define SERVEURSYNERGIE_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include "Reseau/client.h"
#include "Reseau/mangepaquets.h"
#include "Reseau/Paquets/basepaquetserveur.h"
#include "fichier.h"
#include "projet.h"

class ServeurSynergie : public QObject
{
    Q_OBJECT
public:
    static ServeurSynergie* getInstance();

    bool Demarrer();
    bool Arreter();
    void EnleverClient(Client* client);
    void AjouterClient(Client* client);
    void EnvoyerPaquetATous(BasePaquetServeur* paquet, Client* exception = 0);
    void EnvoyerPaquetAListe(QList<Client*>* clients, BasePaquetServeur* paquet, Client* exception = 0);
    MangePaquets* getMangePaquets();
    QMap<int, Client*>* getClients();
    Projet* getProjet();
    bool NouveauProjet(QString nom);

private:
    explicit ServeurSynergie(QObject* parent = 0);

    static ServeurSynergie* m_Instance;

    Projet* m_Projet;
    QTcpServer* m_Ecouteur;
    MangePaquets* m_MangePaquets;
    QMap<int, Client*>* m_Clients;

signals:

public slots:
    void slNouveauClient();
};

#endif // SERVEURSYNERGIE_H
