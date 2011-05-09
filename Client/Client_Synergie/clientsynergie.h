#ifndef CLIENTSYNERGIE_H
#define CLIENTSYNERGIE_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include "Reseau/connexion.h"
#include "Reseau/depaqueteur.h"
#include "collegue.h"
#include "feuille.h"

class ClientSynergie : public QObject
{
    Q_OBJECT
public:
    static ClientSynergie* Instance();

    bool Connecter(QString adresse, int port);
    void Renommer(QString nom);
    void AjouterFeuille(QString nom, int id);
    void ConnexionCollegue(Collegue* collegue);
    void DeconnexionCollegue(int id);

    Connexion* getConnexion();
    Depaqueteur* getDepaqueteur();
    Collegue* getCollegue(int id);
    int getFeuille(Feuille* feuille);
    Feuille* getFeuille(int id);
    QString getNom();

private:
    explicit ClientSynergie(QObject *parent = 0);

    static ClientSynergie* m_Instance;

    QString m_Nom;
    Connexion* m_Connexion;
    QMap<int, Feuille*>* m_Feuilles;
    QMap<int, Collegue*>* m_Collegues;

signals:
    void siConnexionCollegue(Collegue* collegue);
    void siDeconnexionCollegue(Collegue* collegue);
    void siAjoutFeuille(Feuille* feuille);
    void siSupressionFeuille(Feuille* feuille);

public slots:
    void slInsertionTexte(int id, int pos, QString texte);
    void slEffacementTexte(int id, int pos, int longeur);
    void slEnvoiTexteChat(QString Texte);
    void slReponseCheckSum(int id);

};

#endif // CLIENTSYNERGIE_H
