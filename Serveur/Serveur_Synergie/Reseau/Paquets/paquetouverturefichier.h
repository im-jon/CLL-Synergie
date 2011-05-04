#ifndef PAQUETOUVERTUREFICHIER_H
#define PAQUETOUVERTUREFICHIER_H

#include "basepaquetserveur.h"
#include "fichier.h"

class PaquetOuvertureFichier : public BasePaquetServeur
{
public:
    PaquetOuvertureFichier(Fichier* fichier);
};

#endif // PAQUETOUVERTUREFICHIER_H
