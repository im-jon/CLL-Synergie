#ifndef PAQUETDONNEES_H
#define PAQUETDONNEES_H

#include "basepaquet.h"
#include <QByteArray>
#include "Reseau/transfer.h"

class PaquetDonnees : public BasePaquet
{
public:
    PaquetDonnees(Transfer* transfer);
};

#endif // PAQUETDONNEES_H
