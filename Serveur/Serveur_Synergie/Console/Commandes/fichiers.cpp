#include "fichiers.h"
#include "serveur.h"
#include <QMapIterator>
#include <QStringBuilder>
#include <QStringList>
#include "fichier.h"

Fichiers::Fichiers()
{
    m_MotsCle << "fichiers" << "files";
    m_ArgsMin = 0;
    m_Description = "Donne une liste des fichiers du projet.";
}

QString Fichiers::Executer(Arguments* arguments)
{
    QString retour;
    bool ouvertSeulement = false;
    if (arguments->argument("o"))
    {
        ouvertSeulement = true;
    }

    QMapIterator<int, Fichier*> iterateur(*Serveur::Instance()->getProjet()->getFichiers());
    retour = "Liste des fichiers du projet :";
    while (iterateur.hasNext())
    {
        iterateur.next();
        bool visible = true;
        if (ouvertSeulement)
        {
            visible = iterateur.value()->charge();
        }

        if (visible)
        {
            retour = retour %
                    "\n" % iterateur.value()->getChemin() %
                    " (" % QString::number(iterateur.key()) %
                    ") Clients: " % QString::number(iterateur.value()->getClients()->count());
        }
    }
    return retour;
}
