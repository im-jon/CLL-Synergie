#ifndef CURSEUR_H
#define CURSEUR_H

#include "client.h"

class Client;

class Curseur
{
public:
    Curseur(Client* client);

    int getLigne();
    int getIndex();
    void setLigne(int ligne);
    void setIndex(int index);

private:
    Client* m_Client;
    int m_Ligne;
    int m_Index;
};

#endif // CURSEUR_H
