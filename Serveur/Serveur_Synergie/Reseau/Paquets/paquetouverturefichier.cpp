#include "paquetouverturefichier.h"
#include <QStringBuilder>
#include <QFile>
#include <QTextStream>

PaquetOuvertureFichier::PaquetOuvertureFichier(Client* client, Fichier* fichier)
    : BasePaquet(10)
{
    *m_Stream << fichier->getID();
    *m_Stream << fichier->getClients()->count() - 1;

    Client* collegue;
    foreach (collegue, *fichier->getClients())
    {
        if (collegue != client)
        {
            *m_Stream << collegue->getID();
            *m_Stream << fichier->getCurseur(collegue)->getPosition();
        }
    }
}
