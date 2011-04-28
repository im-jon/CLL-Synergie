#include "mangepaquetsserveur.h"
#include <QDataStream>
#include "Console/console.h"

MangePaquetsServeur::MangePaquetsServeur(QObject *parent) :
    QObject(parent)
{
}

void MangePaquetsServeur::Interpreter(Client* client, QDataStream* stream)
{
    quint8 id;
    *stream >> id;

    switch (id) {
    case 1:
        Reception_ChangerNom(client, stream);
        break;
    default:
        Console::getInstance()->Imprimer("Reception d'un paquet inconnu #" + QString::number(id));
        break;
    }
}

void MangePaquetsServeur::Reception_ChangerNom(Client* client, QDataStream* stream)
{
    QString nom;

    *stream >> nom;

    client->setNom(nom);
}
