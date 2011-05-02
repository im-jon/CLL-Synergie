#include "basepaquetserveur.h"
#include <QDebug>

BasePaquetServeur::BasePaquetServeur(qint8 id)
{
    m_Stream = new QDataStream(&m_Buffer, QIODevice::WriteOnly);

    *m_Stream << id;
}

QByteArray BasePaquetServeur::getBuffer()
{
    int number = m_Buffer.length();
    QByteArray ba;
    QDataStream* stream = new QDataStream(&ba, QIODevice::WriteOnly);
    *stream << number;
    m_Buffer.insert(0, ba);
    return m_Buffer;
}
