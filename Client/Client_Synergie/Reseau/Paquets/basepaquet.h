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
    BasePaquet(qint8 id);

    QDataStream* m_Stream;
};

#endif // BASEPAQUET_H
