#ifndef CLIENTSYNERGIE_H
#define CLIENTSYNERGIE_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include "Reseau/connexion.h"
#include "Reseau/depaqueteur.h"
#include "collegue.h"
#include "feuille.h"
#include "chat.h"

class ClientSynergie : public QObject
{
    Q_OBJECT
public:
    static ClientSynergie* Instance();

    bool Connecter(QString adresse, int port);
    void AjouterFeuille(QString nom, int id);
    void ConnexionCollegue(Collegue* collegue);
    void DeconnexionCollegue(int id);
    void Authentifier();

    Connexion* getConnexion();
    Chat* getChat();
    Depaqueteur* getDepaqueteur();
    Collegue* getCollegue(int id);
    int getFeuille(Feuille* feuille);
    Feuille* getFeuille(int id);
    QString getNom();
    QColor getCouleur();

    void setNom(QString nom);
    void setCouleur(QColor couleur);

private:
    explicit ClientSynergie(QObject *parent = 0);

    static ClientSynergie* m_Instance;

    QString m_Nom;
    QColor m_Couleur;
    Connexion* m_Connexion;
    Chat* m_Chat;
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
    void slVerification(int id, bool reponse);
    void slFermerFichier(int id);
    void slLigneChangee(int feuille, int ligne);

};

#endif // CLIENTSYNERGIE_H
