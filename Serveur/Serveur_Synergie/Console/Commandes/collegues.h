#ifndef COLLEGUES_H
#define COLLEGUES_H

#include <QStringList>
#include "basecommande.h"

class Collegues : public BaseCommande
{
public:
    Collegues();
protected:
    QString Executer(const QStringList& arguments);

};

#endif // COLLEGUES_H
