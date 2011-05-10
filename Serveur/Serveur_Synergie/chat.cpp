#include "chat.h"
#include "Reseau/Paquets/paquetmessagechat.h"

Chat::Chat(QObject *parent) :
    QObject(parent)
{
    m_Messages = new QList<Message*>;
}

void Chat::NouveauMessage(Message* message)
{
    m_Messages->append(message);
    Serveur::Instance()->getClients()->EnvoyerPaquetATous(
                new PaquetMessageChat(message), message->getAuteur());
}

QList<Message*>* Chat::getMessages()
{
    return m_Messages;
}
