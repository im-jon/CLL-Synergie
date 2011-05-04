#ifndef PAQUETDECONNEXIONCOLLEGUE_H
#define PAQUETDECONNEXIONCOLLEGUE_H

#include "basepaquetserveur.h"
#include "Reseau/client.h"

class PaquetDeconnexionCollegue : public BasePaquetServeur
{
public:
    PaquetDeconnexionCollegue(Client* client);
};

#endif // PAQUETDECONNEXIONCOLLEGUE_H
