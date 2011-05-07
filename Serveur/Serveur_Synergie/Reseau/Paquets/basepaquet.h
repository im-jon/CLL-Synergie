#ifndef BASEPAQUET_H
#define BASEPAQUET_H

#include <QByteArray>
#include <QDataStream>

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
