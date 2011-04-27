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

    QString getNom();
    void setNom(QString nom);
    void EnvoyerPaquet(BasePaquetServeur* paquet);

private:
    QString m_Nom;
    int m_ID;
    QTcpSocket* m_Socket;

signals:

public slots:
    void slPretALire();
    void slOnDeconnection();
    int getID();
};

#endif // CLIENT_H
