#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Paquets/basepaquetserveur.h"
#include "transfer.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(int id, QTcpSocket* socket);

    void EnvoyerPaquet(BasePaquetServeur* paquet);
    void EnvoyerFeuille(int id);

    QString getNom();
    QString getIP();
    Transfer* getTransfer();

    void setNom(QString nom);

private:
    void LirePaquet();

    int m_ID;
    QString m_Nom;
    QTcpSocket* m_Socket;
    Transfer* m_Transfer;

signals:

public slots:
    void slPretALire();
    void slOnDeconnection();
    int getID();
};

#endif // CLIENT_H
