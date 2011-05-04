#ifndef TRANSFER_H
#define TRANSFER_H

#include <QFile>
#include <QTextStream>
#include "fichier.h"

class Fichier;

class Transfer
{
public:
    Transfer(Fichier* fichier);
    QString LireBloc();
    Fichier* getFichier();
    bool estFini();

private:
    QTextStream* m_Stream;
    Fichier* m_Fichier;
    bool m_Fini;
};

#endif // TRANSFER_H
