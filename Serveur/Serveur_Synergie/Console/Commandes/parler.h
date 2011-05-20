#ifndef PARLER_H
#define PARLER_H

#include "basecommande.h"

class Parler : public BaseCommande
{
public:
    Parler();

protected:
    QString Executer(Arguments* arguments);
};

#endif // PARLER_H
