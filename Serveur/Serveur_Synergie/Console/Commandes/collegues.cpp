#include "collegues.h"
#include <QStringBuilder>
#include <QMapIterator>
#include "serveur.h"


Collegues::Collegues()
{
   m_MotsCle << "collegues" << "qui" << "who";
   m_ArgsMin = 0;
   m_Description = "Donne la liste des collègues connectés ainsi que leur IP.";
}

QString Collegues::Executer(Arguments* argument)
{
    QString retour;
    if (Serveur::Instance()->getClients()->compte() > 0)
    {
        QMapIterator<int, Client*> iterateur(*Serveur::Instance()->getClients()->getClients());
        retour = "Liste des collègues en ligne :";
        while (iterateur.hasNext())
        {
            iterateur.next();
            retour = retour % "\n" %
                    QString::number(iterateur.value()->getID()) %
                    " - " %
                    iterateur.value()->getNom() %
                    " (" % iterateur.value()->getConnexion()->getIP() % ")";
        }
    }
    else
    {
        retour = "Il n'y à aucun collègue en ligne";
    }
    return retour;
}
