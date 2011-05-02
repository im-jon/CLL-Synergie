#ifndef PAQUETCONNEXIONCOLLEGUE_H
#define PAQUETCONNEXIONCOLLEGUE_H

#include "basepaquetserveur.h"
#include "Reseau/client.h"

class PaquetConnexionCollegue : public BasePaquetServeur
{
public:
    PaquetConnexionCollegue(Client* client);
};

#endif // PAQUETCONNEXIONCOLLEGUE_H
