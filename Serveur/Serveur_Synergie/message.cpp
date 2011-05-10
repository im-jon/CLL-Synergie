#include "message.h"

Message::Message(Client* auteur, QString contenu, QObject *parent) :
    QObject(parent)
{
    m_Auteur = auteur;
    m_Contenu = contenu;
}

void Message::Archiver()
{
    // À faire (si on à le temps)
}

Client* Message::getAuteur()
{
    return m_Auteur;
}

QString Message::getContenu()
{
    return m_Contenu;
}
