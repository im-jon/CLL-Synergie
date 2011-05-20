#ifndef VIDER_H
#define VIDER_H

#include "basecommande.h"

class Vider : public BaseCommande
{
public:
    Vider();

protected:
    QString Executer(Arguments arguments);
};

#endif // VIDER_H
