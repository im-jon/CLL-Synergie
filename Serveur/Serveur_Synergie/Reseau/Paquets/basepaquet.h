#ifndef BASEPAQUET_H
#define BASEPAQUET_H

#include <QByteArray>
#include <QDataStream>

// Le paquet regroupe des données que nous voulons envoyer au client. Un paquet
// est construit dans ce format :
// [   Taille (int)  |  ID (ubyte)  |  Données  ]

class BasePaquet
{
public:
    QByteArray getBuffer();

private:
    QByteArray m_Buffer;

protected:
    QDataStream* m_Stream;
    BasePaquet(qint8 id);
};

#endif // BASEPAQUETSERVEUR_H
