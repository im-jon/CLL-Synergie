#include "argument.h"

Argument::Argument(QString nom, QString valeur)
{
    m_Nom = nom;
    m_Valeur = valeur;
}

QString Argument::nom()
{
    return m_Nom;
}

QString Argument::valeur()
{
    return m_Valeur;
}
