#include "paquetouverturefichier.h"
#include <QStringBuilder>
#include <QFile>
#include <QTextStream>

PaquetOuvertureFichier::PaquetOuvertureFichier(Fichier* fichier)
    : BasePaquet(10)
{
    *m_Stream << fichier->getID();
}
