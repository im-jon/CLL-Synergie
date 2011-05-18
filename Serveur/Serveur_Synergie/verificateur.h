#ifndef VERIFICATEUR_H
#define VERIFICATEUR_H

#include <QObject>
#include <QTimer>
#include "clients.h"

class Verificateur : public QObject
{
    Q_OBJECT
public:
    explicit Verificateur(QObject *parent = 0);

    void Demarrer();
    void Arreter();
    void ReceptionReponse(bool reponse, Client* client, Fichier* fichier);

private:
    QTimer* m_Timer;

    void Verifier();

signals:

public slots:
    void slTimer();

};

#endif // VERIFICATEUR_H
