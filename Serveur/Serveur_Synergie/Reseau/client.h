#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Paquets/basepaquetserveur.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* socket);

    void setNom(QString nom);
    void EnvoyerPaquet(BasePaquetServeur* paquet);

private:
    QString m_Nom;
    QTcpSocket* m_Socket;

signals:

public slots:
    void slPretALire();
    void slOnDeconnection();
};

#endif // CLIENT_H
