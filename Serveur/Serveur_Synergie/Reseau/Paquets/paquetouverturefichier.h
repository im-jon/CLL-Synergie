#ifndef PAQUETOUVERTUREFICHIER_H
#define PAQUETOUVERTUREFICHIER_H

#include "basepaquet.h"
#include "fichier.h"

class PaquetOuvertureFichier : public BasePaquet
{
public:
    PaquetOuvertureFichier(Client* client, Fichier* fichier);
};

#endif // PAQUETOUVERTUREFICHIER_H
