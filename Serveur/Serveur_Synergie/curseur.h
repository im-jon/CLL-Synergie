#ifndef CURSEUR_H
#define CURSEUR_H

#include "client.h"

class Client;

class Curseur
{
public:
    Curseur(Client* client);

    int getPosition();
    void setPosition(int position);

private:
    Client* m_Client;
    int m_Position;
};

#endif // CURSEUR_H
