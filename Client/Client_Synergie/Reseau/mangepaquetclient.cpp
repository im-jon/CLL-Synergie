#include "mangepaquetclient.h"
#include <QDataStream>
#include <QDebug>

MangePaquetClient::MangePaquetClient(QObject *parent) :
    QObject(parent)
{
}

void MangePaquetClient::Interpreter(QDataStream* stream)
{
    quint8 id;
    *stream >> id;

    if (id == 1) {
        Reception_ListeCollegues(stream);
    }
}

void MangePaquetClient::Reception_ListeCollegues(QDataStream* stream)
{

}
