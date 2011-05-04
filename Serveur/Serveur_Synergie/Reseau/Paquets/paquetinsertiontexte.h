#ifndef PAQUETINSERTIONTEXTE_H
#define PAQUETINSERTIONTEXTE_H

#include "fichier.h"
#include "basepaquetserveur.h"

class PaquetInsertionTexte : public BasePaquetServeur
{
public:
    PaquetInsertionTexte(Fichier* fichier, QString texte, int position);
};

#endif // PAQUETINSERTIONTEXTE_H
