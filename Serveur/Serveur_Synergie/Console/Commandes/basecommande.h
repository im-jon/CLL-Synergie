#ifndef BASECOMMANDE_H
#define BASECOMMANDE_H

#include <QObject>
#include <QStringList>
#include <QList>

class BaseCommande : public QObject
{
    Q_OBJECT
public:
    static QList<BaseCommande*>* ListeCommandes;
    static void InitialiserListe();

    const QStringList& getMotsCle();
    int getArgsMin();
    QString getDescription();

    virtual QString Executer(const QStringList &arguments);

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
