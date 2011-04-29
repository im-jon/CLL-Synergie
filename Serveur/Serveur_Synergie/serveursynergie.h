#ifndef SERVEURSYNERGIE_H
#define SERVEURSYNERGIE_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include "Reseau/client.h"
#include "Reseau/mangepaquetsserveur.h"

class ServeurSynergie : public QObject
{
    Q_OBJECT
public:
    static ServeurSynergie* getInstance();

    bool Demarrer();
    bool Arreter();
    bool EnleverClient(Client* client);
    MangePaquetsServeur* getMangePaquets();
    QMap<int, Client*>* getClients();
    void NouveauProjet(QString nom);

private:
    static ServeurSynergie* m_Instance;

    explicit ServeurSynergie(QObject *parent = 0);

    QString m_Projet;
    QTcpServer* m_Ecouteur;
    MangePaquetsServeur* m_MangePaquets;
    QMap<int, Client*>* m_Clients;
    int m_GenerateurID; // Sert à attribuer des nombres d'identification aux clients.

signals:

public slots:
    void slNouveauClient();
};

#endif // SERVEURSYNERGIE_H
