#include "paquetreponseverification.h"

PaquetReponseVerification::PaquetReponseVerification(int idFeuille, bool reponse):
    BasePaquet(8)
{
    *m_Stream << idFeuille;
    *m_Stream << reponse;
}
