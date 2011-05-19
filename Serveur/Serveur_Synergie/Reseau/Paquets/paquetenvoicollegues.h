#ifndef PAQUETENVOICOLLEGUES_H
#define PAQUETENVOICOLLEGUES_H

#include "basepaquet.h"
#include "client.h"

class PaquetEnvoiCollegues : public BasePaquet
{
public:
    PaquetEnvoiCollegues(Client* destinataire);
};

#endif // PAQUETENVOICOLLEGUES_H
