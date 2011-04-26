#include "client.h"
#include <QByteArray>
#include <QDataStream>
#include <QtCore>

Client::Client(QTcpSocket* socket)
{
    m_Socket = socket;
    connect(m_Socket, SIGNAL(readyRead()),this,SLOT(slPretALire()));
    connect(m_Socket,SIGNAL(disconnected()),this,SLOT(slOnDeconnection())); // Parenthèses ???
}

void Client:: slPretALire()
{
    QByteArray buffer;
    buffer = m_Socket->readAll();
    QDataStream stream(&buffer, QIODevice::ReadOnly);
    quint8 id;
    stream >> id;

    // Interpréter le paquet

    qDebug() << buffer.length();
}

void Client:: slOnDeconnection()
{

}
