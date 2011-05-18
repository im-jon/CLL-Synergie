#ifndef PAQUETREPONSEVERIFICATION_H
#define PAQUETREPONSEVERIFICATION_H

#include "basepaquet.h"
#include "feuille.h"

class PaquetReponseVerification : public BasePaquet
{
public:
    PaquetReponseVerification(int idFeuille, bool reponse);
};

#endif // PAQUETREPONSEVERIFICATION_H
