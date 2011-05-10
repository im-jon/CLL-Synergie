#ifndef PAQUETCONNEXIONCOLLEGUE_H
#define PAQUETCONNEXIONCOLLEGUE_H

#include "basepaquet.h"
#include "client.h"

class PaquetConnexionCollegue : public BasePaquet
{
public:
    PaquetConnexionCollegue(Client* client);
};

#endif // PAQUETCONNEXIONCOLLEGUE_H
