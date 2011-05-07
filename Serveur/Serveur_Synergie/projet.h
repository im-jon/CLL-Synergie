#ifndef PROJET_H
#define PROJET_H

#include <QObject>
#include <QMap>
#include <QDir>
#include <QStringList>
#include "fichier.h"

class Projet : public QObject
{
    Q_OBJECT
public:
    explicit Projet(QString nom, QObject *parent = 0);

    void Fermer();
    void Sauvegarder();
    QString getNom();
    QString getChemin();
    Fichier* getFichier(int id);
    QMap<int, Fichier*>* getFichiers();

private:
    void Initialiser();
    void AjouterFichier(Fichier* fichier);
    void EnleverFichier(int id);

    QString m_Nom;
    QString m_Chemin;
    QMap<int, Fichier*>* m_Fichiers;

signals:

public slots:

};

#endif // PROJET_H
