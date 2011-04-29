#include "aide.h"
#include <QStringBuilder>
#include <QDebug>

Aide::Aide()
{
    m_MotsCle << "aide" << "help" << "commandes" << "?";
    m_ArgsMin = 0;
    m_Description = "Donne la liste complète des commandes.";
}

QString Aide::Executer(const QStringList& arguments)
{
    QString retour = "Liste des commandes:";
    BaseCommande* commande;

    for (int i = 0; i < BaseCommande::ListeCommandes->length(); i++) {
        commande = BaseCommande::ListeCommandes->at(i);
        retour = retour % "\n" % commande->getMotsCle().first() % "    -    " % commande->getDescription();
    }

    return retour;
}
