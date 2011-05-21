#ifndef REDEMARRER_H
#define REDEMARRER_H

#include "basecommande.h"
#include "serveur.h"

class Redemarrer : public BaseCommande
{
public:
    Redemarrer();

protected:
    QString Executer(Arguments* arguments);
};

#endif // REDEMARRER_H
