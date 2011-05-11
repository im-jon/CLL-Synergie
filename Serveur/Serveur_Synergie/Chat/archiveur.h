#ifndef ARCHIVEUR_H
#define ARCHIVEUR_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include "message.h"

class Archiveur : public QObject
{
    Q_OBJECT
public:
    explicit Archiveur(QObject *parent = 0);

    void Arreter();
    void Archiver(Message* message);
    void Archiver(QList<Message*>* messages);

private:
    void Initialiser();

    QDir* m_Repertoire;
    QFile* m_FichierActuel;
    QTextStream* m_Stream;

signals:

public slots:

};

#endif // ARCHIVEUR_H