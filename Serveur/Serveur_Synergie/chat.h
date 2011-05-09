#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include "Reseau/client.h"
#include "serveur.h"

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);

    void NouveauMessage(Client* auteur, QString message);

signals:

public slots:

};

#endif // CHAT_H
