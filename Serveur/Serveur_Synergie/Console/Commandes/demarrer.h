#ifndef DEMARRER_H
#define DEMARRER_H

#include "basecommande.h"

class Demarrer : public BaseCommande
{
public:
    Demarrer();

protected:
    QString Executer(const QStringList& arguments);
};

#endif // DEMARRER_H
