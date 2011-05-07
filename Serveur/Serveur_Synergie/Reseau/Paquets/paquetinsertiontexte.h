#ifndef PAQUETINSERTIONTEXTE_H
#define PAQUETINSERTIONTEXTE_H

#include "fichier.h"
#include "basepaquet.h"

class PaquetInsertionTexte : public BasePaquet
{
public:
    PaquetInsertionTexte(Fichier* fichier, QString texte, int position);
};

#endif // PAQUETINSERTIONTEXTE_H
