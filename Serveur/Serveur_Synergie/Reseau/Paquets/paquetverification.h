#ifndef PAQUETVERIFICATION_H
#define PAQUETVERIFICATION_H

#include "basepaquet.h"
#include "fichier.h"

class PaquetVerification : public BasePaquet
{
public:
    PaquetVerification(Fichier* fichier);
};

#endif // PAQUETVERIFICATION_H
