#ifndef PROJET_H
#define PROJET_H

#include <QObject>
#include <QMap>
#include <QDir>
#include "fichier.h"
#include "dossier.h"

class Projet : public QObject
{
    Q_OBJECT
public:
    explicit Projet(QString nom, QObject *parent = 0);
    QString getNom();
    void Initialiser();

private:
    QString m_Nom;
    Dossier* m_DossierPrincipal;

signals:

public slots:

};

#endif // PROJET_H
