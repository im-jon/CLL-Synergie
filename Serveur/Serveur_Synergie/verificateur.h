#ifndef VERIFICATEUR_H
#define VERIFICATEUR_H

#include <QObject>
#include <QTimer>

#include "clients.h"

// Le vérification a pour fonction de vérifier si les fichiers du client et du
// serveur sont bien synchronisé. Le processus est simple, le serveur envoi
// une vérification selon une intervalle. La vérification consiste à comparer la
// taille des deux fichiers et se fait au niveau du client. Si la vérification
// est un succès, le client réponds par une bonne réponse. Dans le cas contraire,
// celui-ci réponds par une mauvaise réponse. Si le nombre de mauvaises réponses
// dépasse le seuil autorisé, le fichier est automatiquement renvoyé au client.

class Verificateur : public QObject
{
    Q_OBJECT
public:
    explicit Verificateur(QObject *parent = 0);

    void Demarrer();
    void Arreter();
    void ReceptionReponse(bool reponse, Client* client, Fichier* fichier);

private:
    QTimer* m_Timer;

    void Verifier();

signals:

public slots:
    void slTimer();

};

#endif // VERIFICATEUR_H
