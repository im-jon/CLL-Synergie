#ifndef PAQUETEFFACEMENTTEXTE_H
#define PAQUETEFFACEMENTTEXTE_H

#include "basepaquet.h"
#include "fichier.h"

class PaquetEffacementTexte : public BasePaquet
{
public:
    PaquetEffacementTexte(Client* auteur, Fichier* fichier, int position, int longeur);
};

#endif // PAQUETEFFACEMENTTEXTE_H
