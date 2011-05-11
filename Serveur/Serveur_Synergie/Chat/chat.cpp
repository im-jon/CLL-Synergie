#include "chat.h"
#include "Reseau/Paquets/paquetmessagechat.h"

const int Seuil = 100; // Nombre de messages maximum que la liste peut contenir.

Chat::Chat(QObject *parent) :
    QObject(parent)
{
    m_Messages = new QList<Message*>;
    m_Archiveur = new Archiveur(this);
}

void Chat::NouveauMessage(Message* message)
{
    m_Messages->append(message);

    // Si le nombre de messages dépasse le seuil, on efface le premier de la liste pour garder
    // une quantité de messages constante.
    if (m_Messages->count() >= Seuil)
    {
        m_Archiveur->Archiver(m_Messages->first());
        m_Messages->removeFirst();
    }

    Serveur::Instance()->getClients()->EnvoyerPaquetATous(
                new PaquetMessageChat(message), message->getAuteur());
}

QList<Message*>* Chat::getMessages()
{
    return m_Messages;
}

Archiveur* Chat::getArchiveur()
{
    return m_Archiveur;
}
