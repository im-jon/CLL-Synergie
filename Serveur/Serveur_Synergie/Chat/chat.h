#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include <QList>

#include "client.h"
#include "serveur.h"
#include "message.h"
#include "archiveur.h"

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);

    void Demarrer();
    void Arreter();
    void NouveauMessage(Message* message);
    QList<Message*>* getMessages();
    Archiveur* getArchiveur();


private:
    bool m_Actif;
    QList<Message*>* m_Messages;
    Archiveur* m_Archiveur;

};

#endif // CHAT_H
