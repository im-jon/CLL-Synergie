#ifndef PAQUETDECONNEXIONCOLLEGUE_H
#define PAQUETDECONNEXIONCOLLEGUE_H

#include "basepaquet.h"
#include "client.h"

class PaquetDeconnexionCollegue : public BasePaquet
{
public:
    PaquetDeconnexionCollegue(Client* client);
};

#endif // PAQUETDECONNEXIONCOLLEGUE_H
