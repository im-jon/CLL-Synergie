#include "basepaquet.h"

BasePaquet::BasePaquet(qint8 id)
{
    m_Stream = new QDataStream(&m_Buffer, QIODevice::WriteOnly);

    *m_Stream << id;
}

QByteArray BasePaquet::getBuffer()
{
    return m_Buffer;
}
