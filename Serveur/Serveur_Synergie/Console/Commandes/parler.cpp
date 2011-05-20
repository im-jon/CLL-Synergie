#include "parler.h"

Parler::Parler()
{
    m_MotsCle << "parler" << "dire" << "say";
    m_ArgsMin = 1;
    m_Description = "Envoi un message global sur le chat";
}

QString Parler::Executer(Arguments arguments)
{
    Argument* messageArg = arguments["m"];
    if (messageArg)
    {
        // À faire : Envoyer un paquet aux clients.
        return "Global: " + messageArg->valeur();
    }
    return "";
}
