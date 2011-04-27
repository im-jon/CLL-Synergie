#include "mangepaquetsserveur.h"
#include <QDataStream>
#include <QDebug>

MangePaquetsServeur::MangePaquetsServeur(QObject *parent) :
    QObject(parent)
{
}

void MangePaquetsServeur::Interpreter(Client* client, QDataStream* stream)
{
    quint8 id;
    *stream >> id;

    if (id == 1) {
        Reception_ChangerNom(client, stream);
    }
}

void MangePaquetsServeur::Reception_ChangerNom(Client* client, QDataStream* stream)
{
    QString nom;

    *stream >> nom;

    client->setNom(nom);
}
