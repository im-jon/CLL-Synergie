#ifndef COLLEGUE_H
#define COLLEGUE_H

#include <QObject>

class Collegue : public QObject
{
    Q_OBJECT
public:
    explicit Collegue(int id, QString nom, QObject *parent = 0);

    int getID();
    QString getNom();

private:
    int m_ID;
    QString m_Nom;

signals:

public slots:

};

#endif // COLLEGUE_H
