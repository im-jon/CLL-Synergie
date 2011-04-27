#ifndef SERVEURSYNERGIE_H
#define SERVEURSYNERGIE_H

#include <QObject>
#include <QTcpServer>
#include "Reseau/client.h"
#include "Reseau/mangepaquetsserveur.h"
#include <QMap>

class ServeurSynergie : public QObject
{
    Q_OBJECT
public:
    static ServeurSynergie* getInstance();

    bool Demarrer();
    bool Arreter();
    MangePaquetsServeur* getMangePaquets();

private:
    static ServeurSynergie* m_Instance;

     explicit ServeurSynergie(QObject *parent = 0);
    QTcpServer* m_Ecouteur;
    MangePaquetsServeur* m_MangePaquets;
    QMap<int, Client*> m_Clients;
    int m_ID;

signals:

public slots:
    void slNouveauClient();
};

#endif // SERVEURSYNERGIE_H
