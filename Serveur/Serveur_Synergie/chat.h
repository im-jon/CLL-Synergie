#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QList>
#include "client.h"
#include "serveur.h"
#include "message.h"

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);

    void NouveauMessage(Message* message);
    QList<Message*>* getMessages();

private:
    QList<Message*>* m_Messages;

signals:

public slots:

};

#endif // CHAT_H
