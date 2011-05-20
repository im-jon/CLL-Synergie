#ifndef DEMARRER_H
#define DEMARRER_H

#include "basecommande.h"

class Demarrer : public BaseCommande
{
public:
    Demarrer();

protected:
    QString Executer(Arguments* arguments);
};

#endif // DEMARRER_H
