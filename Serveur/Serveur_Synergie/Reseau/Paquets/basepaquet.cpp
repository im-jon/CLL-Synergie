#include "basepaquet.h"

BasePaquet::BasePaquet(qint8 id)
{
    m_Stream = new QDataStream(&m_Buffer, QIODevice::WriteOnly);

    *m_Stream << id;
}

QByteArray BasePaquet::getBuffer()
{
    // On convertit la valeur de 'taille' en tableau de bytes et on l'insère
    // au début du buffer
    int taille = m_Buffer.length();
    m_Buffer.prepend(reinterpret_cast<const char*>(&taille), sizeof(taille));

    return m_Buffer;
}
