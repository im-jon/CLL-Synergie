#ifndef PAQUETOUVRIRFEUILLE_H
#define PAQUETOUVRIRFEUILLE_H

#include "basepaquet.h"
#include "client.h"
#include "fichier.h"

class PaquetOuvrirFeuille : public BasePaquet
{
public:
    PaquetOuvrirFeuille(Client* client, Fichier* fichier);
};

#endif // PAQUETOUVRIRFEUILLE_H
