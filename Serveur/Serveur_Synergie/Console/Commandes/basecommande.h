#ifndef BASECOMMANDE_H
#define BASECOMMANDE_H

#include <QObject>
#include <QStringList>
#include <QList>
#include "../arguments.h"

class BaseCommande : public QObject
{
    Q_OBJECT
public:
    static QList<BaseCommande*>* ListeCommandes;
    static void InitialiserListe();

    const QStringList& getMotsCle();
    int getArgsMin();
    QString getDescription();

    virtual QString Executer(Arguments arguments);

protected:
    explicit BaseCommande();

    QStringList m_MotsCle;
    int m_ArgsMin;
    QString m_Description;


private:

signals:

public slots:

};

#endif // BASECOMMANDE_H
