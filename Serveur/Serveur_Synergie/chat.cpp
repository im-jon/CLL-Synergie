#include "chat.h"
#include "Reseau/Paquets/paquetmessagechat.h"

const int Seuil = 100; // Nombre de messages maximum que la liste peut contenir.

Chat::Chat(QObject *parent) :
    QObject(parent)
{
    m_Messages = new QList<Message*>;
}

void Chat::NouveauMessage(Message* message)
{
    m_Messages->append(message);

    // Si le nombre de messages dépasse le seuil, on efface le premier de la liste pour garder
    // une quantité de messages constante.
    if (m_Messages->count() >= Seuil)
    {
        // m_Messages->first()->Archiver();
        m_Messages->removeFirst();
    }

    Serveur::Instance()->getClients()->EnvoyerPaquetATous(
                new PaquetMessageChat(message), message->getAuteur());
}

QList<Message*>* Chat::getMessages()
{
    return m_Messages;
}
