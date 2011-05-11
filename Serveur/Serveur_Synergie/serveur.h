#ifndef SERVEUR_H
#define SERVEUR_H

#include <QObject>
#include <QTcpServer>
#include <QMap>
#include "clients.h"
#include "Reseau/depaqueteur.h"
#include "Reseau/Paquets/basepaquet.h"
#include "fichier.h"
#include "projet.h"
#include "Chat/chat.h"
#include "verificateur.h"

class Chat;

class Serveur : public QObject
{
    Q_OBJECT
public:
    static Serveur* Instance();

    bool Demarrer();
    bool Arreter();
    Depaqueteur* getDepaqueteur();
    Projet* getProjet();
    Clients* getClients();
    Chat* getChat();
    Verificateur* getVerificateur();

private:
    explicit Serveur(QObject* parent = 0);

    static Serveur* m_Instance;

    Projet* m_Projet;
    Clients* m_Clients;
    QTcpServer* m_Ecouteur;
    Depaqueteur* m_Depaqueteur;
    Chat* m_Chat;
    Verificateur* m_Verificateur;


signals:

public slots:
    void slNouveauClient();
};

#endif // SERVEUR_H
