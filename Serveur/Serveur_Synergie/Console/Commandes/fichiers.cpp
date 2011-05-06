#include "fichiers.h"
#include "serveursynergie.h"
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

QString Fichiers::Executer(const QStringList& arguments)
{
    QString retour;
    if (ServeurSynergie::getInstance()->getProjet()->getFichiers()->count() > 0) {
        QMapIterator<int, Fichier*> iterateur(*ServeurSynergie::getInstance()->getProjet()->getFichiers());
        retour = "Liste des fichiers du projet :";
        while (iterateur.hasNext()) {
            iterateur.next();
            retour = retour %
                    "\n" % iterateur.value()->getChemin() %
                    " (" % QString::number(iterateur.key()) %
                    ") Clients: " % QString::number(iterateur.value()->getClients()->count());
        }
    } else {
        retour = "Il n'y à aucun fichiers dans le projet actuel";
    }
    return retour;
}
