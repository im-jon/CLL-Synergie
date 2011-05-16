#ifndef PAQUETCHANGERLIGNE_H
#define PAQUETCHANGERLIGNE_H

#include "basepaquet.h"
#include "client.h"
#include "fichier.h"

class PaquetChangerLigne : public BasePaquet
{
public:
    PaquetChangerLigne(Client* client, Fichier* fichier);
};

#endif // PAQUETCHANGERLIGNE_H
