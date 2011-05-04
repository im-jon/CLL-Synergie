#ifndef PAQUETEFFACEMENTTEXTE_H
#define PAQUETEFFACEMENTTEXTE_H

#include "basepaquetserveur.h"
#include "fichier.h"

class PaquetEffacementTexte : public BasePaquetServeur
{
public:
    PaquetEffacementTexte(Fichier* fichier, int position, int longeur);
};

#endif // PAQUETEFFACEMENTTEXTE_H
