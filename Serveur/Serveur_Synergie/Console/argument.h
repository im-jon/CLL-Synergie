#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <QtCore>

class Argument
{
public:
    Argument(QString nom, QString valeur);
    QString nom();
    QString valeur();

private:
    QString m_Nom;
    QString m_Valeur;
};

#endif // ARGUMENT_H
