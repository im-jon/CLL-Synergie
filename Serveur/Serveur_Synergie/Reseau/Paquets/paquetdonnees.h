#ifndef PAQUETDONNEES_H
#define PAQUETDONNEES_H

#include "basepaquetserveur.h"
#include <QByteArray>
#include "Reseau/transfer.h"

class PaquetDonnees : public BasePaquetServeur
{
public:
    PaquetDonnees(Transfer* transfer);
};

#endif // PAQUETDONNEES_H
