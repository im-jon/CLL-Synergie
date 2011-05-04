#include "paquetdeconnexioncollegue.h"

PaquetDeconnexionCollegue::PaquetDeconnexionCollegue(Client* client)
    : BasePaquetServeur((qint8)4)
{
    *m_Stream << client->getID();
}
