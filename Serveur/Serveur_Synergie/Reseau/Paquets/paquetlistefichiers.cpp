#include "paquetlistefichiers.h"
#include "serveur.h"
#include "fichier.h"

PaquetListeFichiers::PaquetListeFichiers()
    : BasePaquet(2)
{
    *m_Stream << Serveur::Instance()->getProjet()->getFichiers()->count();

    QMapIterator<int, Fichier*> iterateur(*Serveur::Instance()->getProjet()->getFichiers());
    while (iterateur.hasNext())
    {
        iterateur.next();
        *m_Stream << iterateur.key();
        *m_Stream << iterateur.value()->getChemin();
    } 
}
