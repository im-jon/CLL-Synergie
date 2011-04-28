#include "basepaquetserveur.h"

BasePaquetServeur::BasePaquetServeur(qint8 id)
{
    m_Stream = new QDataStream(&m_Buffer, QIODevice::WriteOnly);

    *m_Stream << id;
}

QByteArray BasePaquetServeur::getBuffer()
{
    return m_Buffer;
}
