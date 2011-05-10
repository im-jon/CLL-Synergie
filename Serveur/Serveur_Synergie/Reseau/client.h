#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "Paquets/basepaquet.h"
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
    explicit Client(QTcpSocket* socket, QObject *parent = 0);

    void Authentifier(QString nom);
    void Deconnecter();
    void EnvoyerPaquet(BasePaquet* paquet);
    void OuvrirFichier(Fichier* fichier);
    void FermerFichier(Fichier* fichier);
    void EnvoyerFichier(Fichier* fichier, bool onglet = true);
    void FinTransfer(int id);

    QString getNom();
    QString getIP();
    int getID();
    Transfer* getTransfer(int index);
    QList<Fichier*>* getFichiers();
    int getMauvaisesReponses();

    void setNom(QString nom);
    void setMauvaisesReponses(int valeur);

private:
    void LirePaquet();

    static int GenerateurID;

    int m_ID;
    QString m_Nom;
    QTcpSocket* m_Socket;
    QMap<int, Transfer*>* m_Transfers;
    QList<Fichier*>* m_FichiersOuverts;
    int m_MauvaisesReponses;

signals:
    void siDeconnexion(Client* client);

public slots:
    void slPretALire();
    void slDeconnection();
    void slFinTransfer(int id);
};

#endif // CLIENT_H
