#ifndef BASEPAQUETSERVEUR_H
#define BASEPAQUETSERVEUR_H

#include <QByteArray>
#include <QDataStream>

class BasePaquetServeur
{
public:
    QByteArray getBuffer();

private:
    QByteArray m_Buffer;

protected:
    QDataStream* m_Stream;
    BasePaquetServeur(qint8 id);
};

#endif // BASEPAQUETSERVEUR_H
