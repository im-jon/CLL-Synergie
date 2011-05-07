#ifndef CLIENTSYNERGIE_H
#define CLIENTSYNERGIE_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include "Reseau/connexion.h"
#include "Reseau/mangepaquetclient.h"
#include "collegue.h"
#include "feuille.h"

class ClientSynergie : public QObject
{
    Q_OBJECT
public:
    static ClientSynergie* getInstance();

    bool Connecter(QString adresse, int port);
    void Renommer(QString nom);
    void AjouterFeuille(QString nom, int id);
    void ConnexionCollegue(Collegue* collegue);
    void DeconnexionCollegue(int id);

    Connexion* getConnexion();
    MangePaquetClient* getMangePaquets();
    Collegue* getCollegue(int id);
    int getFeuille(Feuille* feuille);
    Feuille* getFeuille(int id);

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

};

#endif // CLIENTSYNERGIE_H
