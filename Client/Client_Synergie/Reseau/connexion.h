#ifndef CONNEXION_H
#define CONNEXION_H

#include <QObject>
#include <QTcpSocket>
#include <QMap>
#include "Paquets/basepaquet.h"
#include "mangepaquetclient.h"

class Connexion : public QObject
{
    Q_OBJECT
public:   
    explicit Connexion(QObject *parent = 0);

    bool Connecter(QString, int);
    void EnvoyerPaquet(BasePaquet* paquet);
    MangePaquetClient* getMangePaquets();

private:
    void LirePaquet();

    QTcpSocket* m_Socket;
    MangePaquetClient* m_MangePaquets;

signals:

public slots:
    void slPretALire();
};

#endif // CONNEXION_H
