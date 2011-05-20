#include "projetcommande.h"

ProjetCommande::ProjetCommande()
{
    m_MotsCle << "projet" << "project";
    m_ArgsMin = 1;
    m_Description = "Administration du projet";
}

QString ProjetCommande::Executer(Arguments* arguments)
{
    Argument* argument;

    argument = arguments->argument("c");
    if (argument)
    {
        // Change le projet
    }
}
