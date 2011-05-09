#include "paquetreponsechecksum.h"

paquetReponseCheckSum::paquetReponseCheckSum(int id):
    BasePaquet(8)
{
    *m_Stream << id;
}
