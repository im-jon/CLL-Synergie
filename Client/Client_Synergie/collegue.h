#ifndef COLLEGUE_H
#define COLLEGUE_H

#include <QObject>
#include <QColor>

class Collegue : public QObject
{
    Q_OBJECT
public:
    explicit Collegue(int id, QString nom, QColor couleur, QObject *parent = 0);

    int getID();
    QString getNom();
    QColor getCouleur();

private:
    int m_ID;
    QString m_Nom;
    QColor m_Couleur;

signals:

public slots:

};

#endif // COLLEGUE_H
