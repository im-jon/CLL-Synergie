#include <QMapIterator>

#include "verificateur.h"
#include "serveur.h"
#include "fichier.h"

#include "Reseau/Paquets/paquetverification.h"
#include "Reseau/Paquets/paquetnettoyerfichier.h"

const int Seuil = 5; // Le seuil de mauvaises réponses.
const int Intervalle = 1000; // Fréquence des reqûetes de vérification en millisecondes.

Verificateur::Verificateur(QObject *parent) :
    QObject(parent)
{
    m_Timer = new QTimer(this);

    connect (m_Timer, SIGNAL(timeout()), this, SLOT(slTimer()));
}

void Verificateur::Demarrer()
{
    m_Timer->start(Intervalle);
}

void Verificateur::Arreter()
{
    m_Timer->stop();
}

void Verificateur::Verifier()
{
    QMapIterator<int, Fichier*> iterateur(*Serveur::Instance()->getProjet()->getFichiers());
    while (iterateur.hasNext())
    {
        iterateur.next();

        Fichier* fichier = iterateur.value();

        if (fichier->nombreClients() > 0)
        {
            Client* client;
            foreach (client, *fichier->getClients())
            {
                if (!client->getTransfer(fichier->getID()))
                {
                    client->EnvoyerPaquet(new PaquetVerification(fichier));
                }
            }
        }
    }
}

void Verificateur::ReceptionReponse(bool reponse, Client *client, Fichier *fichier)
{
    if (reponse == true)
    {
        // Une bonne réponse annule toutes les mauvaises réponses
        if (client->getMauvaisesReponses() > 0)
        {
            client->setMauvaisesReponses(0);
        }
    }
    else
    {
        client->setMauvaisesReponses(client->getMauvaisesReponses() + 1);

        if (client->getMauvaisesReponses() >= Seuil)
        {
            client->EnvoyerPaquet(new PaquetNettoyerFichier(fichier));
            client->EnvoyerFichier(fichier, false);
            client->setMauvaisesReponses(0);
        }
    }
}

void Verificateur::slTimer()
{
    Verifier();
}
