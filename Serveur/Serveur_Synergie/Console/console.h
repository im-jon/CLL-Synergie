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
    static Console* Instance()
    {
        static QMutex mutex;
        if (!m_Instance) {
            mutex.lock();
            m_Instance = new Console;
            mutex.unlock();
        }
        return m_Instance;
    }

    void Ecrire(QString ligne);
    void Imprimer(QString ligne);
    void Vider();

private:
    explicit Console(QObject* parent = 0);
    void Initialiser();
    void InitialiserListeCommandes();
    static Console* m_Instance;
    QMap<QString, BaseCommande*>* m_Commandes;

signals:
    void siSortie(QString ligne);
    void siVider();

public slots:

};

#endif // CONSOLE_H
