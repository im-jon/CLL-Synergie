#ifndef TRANSFER_H
#define TRANSFER_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "fichier.h"

class Fichier;

// Un transfer est utilisé pour envoyé un fichier à un client.
// Le serveur envoi au client le premier bloc de texte et attends
// de recevoir une confirmation que le bloc a été reçu avant de
// procédé au second bloc de texte. Le processus se répète jusqu'à
// ce que tous les blocs soient envoyés.

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
