#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Paquets/basepaquetserveur.h"
#include "fichier.h"
#include "transfer.h"
#include <QMap>
#include <QList>

class Transfer;
class Fichier;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(int id, QTcpSocket* socket);

    void Deconnecter();
    void EnvoyerPaquet(BasePaquetServeur* paquet);
    void OuvrirFichier(Fichier* fichier);
    void FermerFichier(Fichier* fichier);
    void FinTransfer(int id);

    QString getNom();
    QString getIP();
    Transfer* getTransfer(int index);
    QList<Fichier*>* getFichiers();

    void setNom(QString nom);

private:
    void LirePaquet();
    void EnvoyerFichier(Fichier* fichier);

    int m_ID;
    QString m_Nom;
    QTcpSocket* m_Socket;
    QMap<int, Transfer*>* m_Transfers;
    QList<Fichier*>* m_FichiersOuverts;

signals:

public slots:
    void slPretALire();
    void slOnDeconnection();
    int getID();
};

#endif // CLIENT_H
