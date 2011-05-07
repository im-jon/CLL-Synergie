#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include "clients.h"
#include "Reseau/mangepaquets.h"
#include "Reseau/Paquets/basepaquet.h"
#include "fichier.h"
#include "projet.h"

class Serveur : public QObject
{
    Q_OBJECT
public:
    static Serveur* Instance();

    bool Demarrer();
    bool Arreter();
    MangePaquets* getMangePaquets();
    Projet* getProjet();
    Clients* getClients();
    bool NouveauProjet(QString nom);
private:
    explicit Serveur(QObject* parent = 0);

    static Serveur* m_Instance;

    Projet* m_Projet;
    Clients* m_Clients;
    QTcpServer* m_Ecouteur;
    MangePaquets* m_MangePaquets;

signals:

public slots:
    void slNouveauClient();
};

#endif // SERVEUR_H
