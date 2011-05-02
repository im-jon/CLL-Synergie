#include "paquetconnexioncollegue.h"

PaquetConnexionCollegue::PaquetConnexionCollegue(Client* client) :
    BasePaquetServeur((qint8)3)
{
    *m_Stream << client->getNom();
}
