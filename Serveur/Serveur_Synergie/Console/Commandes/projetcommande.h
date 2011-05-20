#ifndef PROJETCOMMANDE_H
#define PROJETCOMMANDE_H

#include "basecommande.h"

class ProjetCommande : public BaseCommande
{
public:
    ProjetCommande();

protected:
    QString Executer(Arguments arguments);
};

#endif // PROJETCOMMANDE_H
