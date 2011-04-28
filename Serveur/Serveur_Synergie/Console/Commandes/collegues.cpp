#include "collegues.h"
#include "QStringBuilder"
#include "QMapIterator"
#include "serveursynergie.h"


Collegues::Collegues()
{
   m_MotsCle << "collegues" << "qui" << "who";
   m_Description = QString::fromUtf8("Donne la liste des collègues connectés ainsi que leur IP.");
}

QString Collegues::Executer()
{
    QString retour = "";
    QMapIterator<int, Client*> iterateur(*ServeurSynergie::getInstance()->getClients());
    while (iterateur.hasNext()) {
        iterateur.next();
        retour = retour % "/n" % QString::number(iterateur.value()->getID()) % " " % iterateur.value()->getNom() % " " % iterateur.value()->getIP();
    }
    return retour;
}
