#ifndef FICHIER_H
#define FICHIER_H

#include <QObject>

class Fichier : public QObject
{
    Q_OBJECT
public:
    explicit Fichier(int id, QString chemin, QObject *parent = 0);

    QString getChemin();
    int getID();

private:
    QString m_Chemin;
    int m_ID;

signals:

public slots:

};

#endif // FICHIER_H
