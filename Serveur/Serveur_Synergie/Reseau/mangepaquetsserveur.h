#ifndef MANGEPAQUETSSERVEUR_H
#define MANGEPAQUETSSERVEUR_H

#include <QObject>
#include "client.h"

class MangePaquetsServeur : public QObject
{
    Q_OBJECT
public:
    explicit MangePaquetsServeur(QObject *parent = 0);
    void Interpreter(Client *client, QDataStream* stream);

private:
    void Reception_ChangerNom(Client *client, QDataStream* stream);

signals:

public slots:

};

#endif // MANGEPAQUETSSERVEUR_H