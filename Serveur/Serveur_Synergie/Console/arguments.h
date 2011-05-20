#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <QList>
#include "argument.h"

class Arguments
{
public:
    Arguments();
    void Ajouter(Argument* argument);
    Argument* operator[](QString argument);
    int count();

private:
    Argument* trouverArgument(QString nom);
    QList<Argument*> m_Arguments;
};

#endif // ARGUMENTS_H
