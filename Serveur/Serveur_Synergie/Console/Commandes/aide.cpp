#include "aide.h"
#include <QStringBuilder>
#include <QDebug>

Aide::Aide()
{
    m_MotsCle << "aide" << "help" << "commandes" << "?";
    m_ArgsMin = 0;
    m_Description = "Donne la liste complète des commandes.";
}

QString Aide::Executer(Arguments* arguments)
{
    QString retour = "Liste des commandes:";

    int max = -1;

    BaseCommande* commande;
    foreach (commande, *BaseCommande::ListeCommandes)
    {
        int longueur = commande->getMotsCle().first().length();
        if (longueur > max)
        {
            max = longueur;
        }
    }

    foreach (commande, *BaseCommande::ListeCommandes)
    {
        QString mot = commande->getMotsCle().first();
        QString vide = QString(max - mot.length(), ' ');
        retour = retour % "\n" % mot % vide % " - " % commande->getDescription();
    }

    return retour;
}
