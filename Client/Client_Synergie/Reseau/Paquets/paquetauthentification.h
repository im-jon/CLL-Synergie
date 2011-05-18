#ifndef PAQUETAUTHENTIFICATION_H
#define PAQUETAUTHENTIFICATION_H

#include "basepaquet.h"
#include "clientsynergie.h"

class PaquetAuthentification : public BasePaquet
{
public:
    PaquetAuthentification(QString nom, QColor couleur);
};

#endif // PAQUETAUTHENTIFICATION_H
