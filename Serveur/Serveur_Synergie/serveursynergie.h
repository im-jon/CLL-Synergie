#ifndef SERVEURSYNERGIE_H
#define SERVEURSYNERGIE_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include "Reseau/client.h"
#include "Reseau/mangepaquetsserveur.h"
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
    bool EnleverClient(Client* client);
    bool AjouterClient(Client* client);
    void EnvoyerPaquetATous(BasePaquetServeur* paquet, Client* exception = 0);
    void EnvoyerPaquetAListe(QList<Client*>* clients, BasePaquetServeur* paquet, Client* exception = 0);
    MangePaquetsServeur* getMangePaquets();
    QMap<int, Client*>* getClients();
    Projet* getProjet();
    bool NouveauProjet(QString nom);

private:
    static ServeurSynergie* m_Instance;

    explicit ServeurSynergie(QObject *parent = 0);

    Projet* m_Projet;
    QTcpServer* m_Ecouteur;
    MangePaquetsServeur* m_MangePaquets;
    QMap<int, Client*>* m_Clients;
    int m_GenerateurIDClient; // Sert à attribuer des nombres d'identification aux clients.

signals:

public slots:
    void slNouveauClient();
};

#endif // SERVEURSYNERGIE_H
