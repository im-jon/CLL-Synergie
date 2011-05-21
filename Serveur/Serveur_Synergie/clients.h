#ifndef CLIENTS_H
#define CLIENTS_H

#include <QObject>
#include <QMap>
#include "client.h"

// Cette classe sert à centraliser la gestion des clients à un niveau global.

class Clients : public QObject
{
    Q_OBJECT
public:
    explicit Clients(QObject *parent = 0);

    void EnleverClient(Client* client);
    void AjouterClient(Client* client);
    void EnvoyerPaquetATous(BasePaquet* paquet, Client* exception = 0);
    static void EnvoyerPaquetAListe(QList<Client*>* clients, BasePaquet* paquet, Client* exception = 0);
    int compte();
    QMap<int, Client*>* getClients();

private:
    QMap<int, Client*>* m_Clients;

public slots:
    void slDeconnexionClient(Client* client);

};

#endif // CLIENTS_H
