#ifndef CLIENTSYNERGIE_H
#define CLIENTSYNERGIE_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include "Reseau/connexion.h"
#include "Reseau/mangepaquetclient.h"
#include "collegue.h"

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
    void ConnexionCollegue(Collegue* collegue);
    void DeconnexionCollegue(int id);
    Collegue* TrouverCollegueParID(int id);

private:
    explicit ClientSynergie(QObject *parent = 0);

    static ClientSynergie* m_Instance;

    QString m_Nom;
    Connexion* m_Connexion;
    QMap<QString, int>* m_Fichiers;
    QMap<int, Collegue*>* m_Collegues;

signals:
    void siConnexionCollegue(Collegue* collegue);
    void siDeconnexionCollegue(Collegue* collegue);

public slots:
    void slInsertionTexte(int id, int pos, QString texte);
    void slEffacementTexte(int id, int pos, int longeur);

};

#endif // CLIENTSYNERGIE_H
