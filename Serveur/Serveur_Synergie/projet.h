#ifndef PROJET_H
#define PROJET_H

#include <QObject>
#include <QMap>

#include "fichier.h"

// TODO: reconstruire entièrement cette classe pour permettre à l'utilisateur de
// choisir librement le répertoire du projet.

class Projet : public QObject
{
    Q_OBJECT
public:
    explicit Projet(QString nom, QObject *parent = 0);

    bool Creer();
    bool Ouvrir();
    bool Fermer();
    bool Sauvegarder();

    QString getNom();
    QString getChemin();
    Fichier* getFichier(int id);
    QMap<int, Fichier*>* getFichiers();

private:
    void AjouterFichier(Fichier* fichier);
    void EnleverFichier(int id);

    QString m_Nom;
    QString m_Chemin;
    QMap<int, Fichier*>* m_Fichiers;
    bool m_Ouvert;

signals:

public slots:

};

#endif // PROJET_H
