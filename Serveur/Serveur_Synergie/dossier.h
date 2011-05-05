#ifndef DOSSIER_H
#define DOSSIER_H

#include <QObject>
#include <QDir>
#include <QMap>
#include "fichier.h"

class Dossier : public QObject
{
    Q_OBJECT
public:
    static int getGenerateurID();
    explicit Dossier(QString chemin, QObject *parent = 0);

private:
    static int GenerateurID;
    QString m_Chemin;
    int m_ID;
    QMap<int, Fichier*>* m_Fichiers;
    QMap<int, Dossier*>* m_Dossiers;

signals:

public slots:

};

#endif // DOSSIER_H
