#ifndef FICHIERS_H
#define FICHIERS_H

#include "basecommande.h"

class Fichiers : public BaseCommande
{
public:
    Fichiers();

protected:
    QString Executer(Arguments* arguments);
};

#endif // FICHIERS_H
