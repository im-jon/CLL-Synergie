#ifndef PROJET_H
#define PROJET_H

#include <QObject>
#include <QMap>
#include <QDir>
#include "fichier.h"

class Projet : public QObject
{
    Q_OBJECT
public:
    explicit Projet(QString nom, QObject *parent = 0);
    QString getNom();
    void Initialiser();
    Fichier* getFichier(int id);

private:
    void AjouterFichier(Fichier* fichier);
    void EnleverFichier(int id);

    QString m_Nom;
    QMap<int, Fichier*>* m_Fichiers;

signals:

public slots:

};

#endif // PROJET_H
