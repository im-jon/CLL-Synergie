#ifndef SERVEURSYNERGIE_H
#define SERVEURSYNERGIE_H

#include <QObject>
#include <QTcpServer>
#include "Reseau/client.h"
#include <QMap>

class ServeurSynergie : public QObject
{
    Q_OBJECT
public:
    explicit ServeurSynergie(QObject *parent = 0);
    bool Demarrer();
    bool Arreter();

private:
    QTcpServer* m_Ecouteur;
    QMap<int, Client*> m_Clients;
    int m_ID;

signals:

public slots:
    void slNouveauClient();
};

#endif // SERVEURSYNERGIE_H
