#include "redemarrer.h"

Redemarrer::Redemarrer()
{
    m_MotsCle << "redemarrer" << "redémarrer" << "reboot" << "restart";
    m_ArgsMin = 0;
    m_Description = "Redémarre le serveur";
}

QString Redemarrer::Executer(Arguments* arguments)
{
    Serveur::Instance()->Arreter();
    Serveur::Instance()->Demarrer();
    return "";
}
