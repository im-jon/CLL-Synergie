#include "basepaquetserveur.h"
#include <QDebug>

BasePaquetServeur::BasePaquetServeur(qint8 id)
{
    m_Stream = new QDataStream(&m_Buffer, QIODevice::WriteOnly);

    *m_Stream << id;
}

QByteArray BasePaquetServeur::getBuffer()
{
    int taille = m_Buffer.length();
    QByteArray ba(reinterpret_cast<const char*>(&taille), sizeof(taille));
    m_Buffer.insert(0, ba);
    return m_Buffer;
}
