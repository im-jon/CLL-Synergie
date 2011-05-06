#ifndef PAQUETENVOICHAT_H
#define PAQUETENVOICHAT_H

#include "basepaquet.h"

class PaquetEnvoiChat : public BasePaquet
{
public:
    PaquetEnvoiChat(QString message);
};

#endif // PAQUETENVOICHAT_H
