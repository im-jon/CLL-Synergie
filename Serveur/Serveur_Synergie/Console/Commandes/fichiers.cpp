#include "fichiers.h"
#include "serveursynergie.h"
#include <QMapIterator>
#include <QStringBuilder>
#include <QStringList>

Fichiers::Fichiers()
{
    m_MotsCle << "fichiers" << "files";
    m_ArgsMin = 0;
    m_Description = "Donne une liste des fichiers du projet.";
}

QString Fichiers::Executer(const QStringList& arguments)
{
    QString retour;
    if (ServeurSynergie::getInstance()->getFichiers()->count() > 0) {
        QMapIterator<int, QString> iterateur(*ServeurSynergie::getInstance()->getFichiers());
        retour = "Liste des fichiers du projet :";
        while (iterateur.hasNext()) {
            iterateur.next();
            retour = retour % "\n" % iterateur.value() % "(" % QString::number(iterateur.key()) % ")";
        }
    } else {
        retour = "Il n'y à aucun fichiers dans le projet actuel";
    }
    return retour;
}
