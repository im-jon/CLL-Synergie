#ifndef PAQUETFERMERFEUILLE_H
#define PAQUETFERMERFEUILLE_H

#include "basepaquet.h"
#include "client.h"
#include "fichier.h"

class PaquetFermerFeuille : public BasePaquet
{
public:
    PaquetFermerFeuille(Client* client, Fichier* fichier);
};

#endif // PAQUETFERMERFEUILLE_H
