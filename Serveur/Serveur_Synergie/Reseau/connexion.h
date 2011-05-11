#ifndef CONNEXION_H
#define CONNEXION_H

#include <QObject>
#include <QTcpSocket>
#include "Paquets/basepaquet.h"
#include "../client.h"

class Client;

class Connexion : public QObject
{
    Q_OBJECT
public:
    explicit Connexion(QTcpSocket* socket, Client* client);
    void Lire();
    void Envoyer(BasePaquet* paquet);
    void EnvoyerBytes(QByteArray donnees);
    void Fermer();

    QString getIP();

private:
    Client* m_Client;
    QTcpSocket* m_Socket;

signals:
    void siDeconnexion();

public slots:
    void slPretALire();
    void slDeconnexion();

};

#endif // CONNEXION_H
