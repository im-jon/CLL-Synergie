#include "curseur.h"

Curseur::Curseur(Client* client)
{
    m_Client = client;
}

int Curseur::getPosition()
{
    return m_Position;
}

void Curseur::setPosition(int position)
{
    m_Position = position;
}
