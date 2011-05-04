#ifndef PAQUETINSERTIONTEXTE_H
#define PAQUETINSERTIONTEXTE_H

#include "basepaquet.h"

class paquetinsertiontexte : public BasePaquet
{
public:
    paquetinsertiontexte(int idfichier, int position, QString Texte);
};

#endif // PAQUETINSERTIONTEXTE_H
