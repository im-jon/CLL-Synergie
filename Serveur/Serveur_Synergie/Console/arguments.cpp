#include "arguments.h"

Arguments::Arguments()
{
}

void Arguments::Ajouter(Argument* argument)
{
    m_Arguments.append(argument);
}

Argument* Arguments::operator [](QString nom)
{
    return trouverArgument(nom);
}

Argument* Arguments::trouverArgument(QString nom)
{
    if (!m_Arguments.empty())
    {
        Argument* argument;
        bool trouve = false;
        QListIterator<Argument*> iterateur(m_Arguments);
        while (iterateur.hasNext() && !trouve)
        {
            argument = iterateur.next();
            if (argument->nom() == nom)
            {
                trouve = true;
            }
        }

        if (trouve)
        {
            return argument;
        }
    }
    return 0;
}

int Arguments::count()
{
    return m_Arguments.count();
}
