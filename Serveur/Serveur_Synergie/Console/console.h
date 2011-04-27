#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include "Commandes/basecommande.h"

class Console : public QObject
{
    Q_OBJECT
public:
    static Console* getInstance();

    void Ecrire(QString ligne);
    void Imprimer(QString ligne);
    void Vider();

private:
    static Console* m_Instance;

    explicit Console(QObject* parent = 0);
    void Initialiser();
    void InitialiserListeCommandes();
    QMap<QString, BaseCommande*>* m_Commandes;

signals:
    void siSortie(QString ligne);
    void siVider();

public slots:

};

#endif // CONSOLE_H
