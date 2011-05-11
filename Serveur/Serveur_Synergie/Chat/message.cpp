#include "message.h"

Message::Message(Client* auteur, QString contenu, QObject *parent) :
    QObject(parent)
{
    m_Auteur = auteur;
    m_Contenu = contenu;
    m_Date = QDateTime::currentDateTime();
}

Client* Message::getAuteur()
{
    return m_Auteur;
}

QString Message::getContenu()
{
    return m_Contenu;
}

QDateTime Message::getDate()
{
    return m_Date;
}
