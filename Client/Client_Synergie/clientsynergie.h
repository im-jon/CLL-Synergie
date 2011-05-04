#ifndef CLIENTSYNERGIE_H
#define CLIENTSYNERGIE_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include "Reseau/connexion.h"
#include "Reseau/mangepaquetclient.h"

class ClientSynergie : public QObject
{
    Q_OBJECT
public:
    static ClientSynergie* getInstance();

    bool Connecter(QString adresse, int port);
    void ChangerNom(QString nom);
    Connexion* getConnexion();
    MangePaquetClient* getMangePaquets();
    void AjouterFichier(QString nom, int id);
    int TrouverFichierParNom(QString nom);
    QString TrouverFichierParID(int id);


private:
    explicit ClientSynergie(QObject *parent = 0);

    static ClientSynergie* m_Instance;

    QString m_Nom;
    Connexion* m_Connexion;
    QMap<QString, int>* m_Fichiers;

signals:

public slots:
    void slOnInsertionTexte(int,int,QString);

};

#endif // CLIENTSYNERGIE_H
