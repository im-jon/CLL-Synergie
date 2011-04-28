#include "demarrer.h"
#include "serveursynergie.h"

Demarrer::Demarrer()
{
    m_MotsCle << "demarrer" << "start";
    m_ArgsMin = 0;
    m_Description = "Démarre le serveur.";
}

QString Demarrer::Executer(const QStringList& arguments)
{

    ServeurSynergie::getInstance()->Demarrer();
    return "";
}
