#ifndef COLLEGUES_H
#define COLLEGUES_H

#include <QStringList>
#include "basecommande.h"

class Collegues : public BaseCommande
{
public:
    Collegues();
protected:
    QString Executer(Arguments arguments);

};

#endif // COLLEGUES_H
