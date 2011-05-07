#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include "fichier.h"

class Fichier;

class Transfer : public QObject
{
    Q_OBJECT
public:
    explicit Transfer(Fichier* fichier, QObject* parent = 0);
    QString LireBloc();
    Fichier* getFichier();

private:
    QTextStream* m_Stream;
    Fichier* m_Fichier;

signals:
    void siFin(int id);

public slots:

};

#endif // TRANSFER2_H
