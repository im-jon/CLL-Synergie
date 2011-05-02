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
    static Connexion* getInstance();

    bool Connecter(QString, int);
    void EnvoyerPaquet(BasePaquet* paquet);
    void ChangerNom(QString nom);
    QMap<QString, int>* getFichiers();
    MangePaquetClient* getMangePaquets();

private:
    static Connexion* m_Instance;

    explicit Connexion(QObject *parent = 0);
    void LirePaquet();

    QMap<QString, int>* m_Fichiers;
    QTcpSocket* m_Socket;
    MangePaquetClient* m_MangePaquets;

signals:

public slots:
    void slPretALire();
};

#endif // CONNEXION_H
