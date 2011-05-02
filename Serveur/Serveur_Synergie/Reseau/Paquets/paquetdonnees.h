#ifndef PAQUETDONNEES_H
#define PAQUETDONNEES_H

#include "basepaquetserveur.h"
#include <QByteArray>

class PaquetDonnees : public BasePaquetServeur
{
public:
    PaquetDonnees(int id, QString donnees);
};

#endif // PAQUETDONNEES_H
