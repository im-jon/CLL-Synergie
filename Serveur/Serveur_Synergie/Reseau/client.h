#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Paquets/basepaquetserveur.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(int id, QTcpSocket* socket);

    void EnvoyerPaquet(BasePaquetServeur* paquet);

    QString getNom();
    QString getIP();

    void setNom(QString nom);

private:
    void LirePaquet();

    int m_ID;
    QString m_Nom;
    QTcpSocket* m_Socket;

signals:

public slots:
    void slPretALire();
    void slOnDeconnection();
    int getID();
};

#endif // CLIENT_H
