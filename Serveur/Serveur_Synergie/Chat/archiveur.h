#ifndef ARCHIVEUR_H
#define ARCHIVEUR_H

#include <QObject>
#include <QDir>
#include <QFile>
#include "message.h"

class Archiveur : public QObject
{
    Q_OBJECT
public:
    explicit Archiveur(QObject *parent = 0);
    void Archiver(Message* message);

private:
    QDir* m_Repertoire;
    void Initialiser();

signals:

public slots:

};

#endif // ARCHIVEUR_H
