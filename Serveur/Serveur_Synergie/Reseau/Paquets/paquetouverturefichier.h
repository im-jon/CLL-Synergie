#ifndef PAQUETOUVERTUREFICHIER_H
#define PAQUETOUVERTUREFICHIER_H

#include <QtCore>
#include "basepaquetserveur.h"

class PaquetOuvertureFichier : public BasePaquetServeur
{
public:
    PaquetOuvertureFichier(QString fichier);
};

#endif // PAQUETOUVERTUREFICHIER_H
