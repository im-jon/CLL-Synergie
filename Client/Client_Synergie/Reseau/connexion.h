#ifndef CONNEXION_H
#define CONNEXION_H

#include <QObject>
#include <QTcpSocket>
#include "Paquets/basepaquet.h"
#include "mangepaquetclient.h"

class Connexion : public QObject
{
    Q_OBJECT
public:   
    static Connexion* getInstance();

    bool Connecter(QString, int);
    void EnvoyerPaquet(BasePaquet* paquet);
    void ChangerNom(QString nom);
    MangePaquetClient* getMangePaquets();

private:
    static Connexion* m_Instance;

    explicit Connexion(QObject *parent = 0);

    QTcpSocket* m_Socket;
    MangePaquetClient* m_MangePaquets;

signals:

public slots:
    void slPretALire();
};

#endif // CONNEXION_H
