#ifndef FEUILLE_H
#define FEUILLE_H

#include <QObject>

class Feuille : public QObject
{
    Q_OBJECT
public:
    explicit Feuille(int id, QString nom, QObject *parent = 0);

    int getID();
    QString getNom();

private:
    int m_ID;
    QString m_Nom;

signals:

public slots:

};

#endif // FEUILLE_H
