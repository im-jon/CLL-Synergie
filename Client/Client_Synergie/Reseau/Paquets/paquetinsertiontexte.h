#ifndef PAQUETINSERTIONTEXTE_H
#define PAQUETINSERTIONTEXTE_H

#include "basepaquet.h"

class PaquetInsertionTexte : public BasePaquet
{
public:
    PaquetInsertionTexte(int id, int pos, QString texte);
};

#endif // PAQUETINSERTIONTEXTE_H
