#include "paquetmauvaisesynchro.h"

paquetMauvaiseSynchro::paquetMauvaiseSynchro(int id):
    BasePaquet(8)
{
    *m_Stream << id;
}
