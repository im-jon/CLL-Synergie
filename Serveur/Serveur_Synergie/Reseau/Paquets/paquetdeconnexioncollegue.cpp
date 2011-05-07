#include "paquetdeconnexioncollegue.h"

PaquetDeconnexionCollegue::PaquetDeconnexionCollegue(Client* client)
    : BasePaquet(4)
{
    *m_Stream << client->getID();
}
