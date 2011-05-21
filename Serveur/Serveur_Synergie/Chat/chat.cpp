#include "chat.h"
#include "Reseau/Paquets/paquetmessagechat.h"

const int Seuil = 50; // Limite du nombre de messages conservés en même temps

Chat::Chat(QObject *parent) :
    QObject(parent)
{
    m_Actif = false;
    m_Messages = new QList<Message*>;
    m_Archiveur = new Archiveur(this);
}

void Chat::Demarrer()
{
    if (!m_Actif)
    {
        m_Archiveur->Demarrer();
        m_Actif = true;
    }
}

void Chat::Arreter()
{
    if (m_Actif)
    {
        m_Archiveur->Archiver(m_Messages);
        m_Archiveur->Arreter();
        m_Actif = false;
    }
}

void Chat::NouveauMessage(Message* message)
{
    if (m_Actif)
    {
        m_Messages->append(message);

        // Si le nombre de messages dépasse le seuil, nous retirons le plus vieux
        // pour garder une quantité de messages constante
        if (m_Messages->count() > Seuil)
        {
            // Nous archivons le message expiré
            m_Archiveur->Archiver(m_Messages->takeFirst());
        }

        Serveur::Instance()->getClients()->EnvoyerPaquetATous(
                    new PaquetMessageChat(message), message->getAuteur());
    }
}

QList<Message*>* Chat::getMessages()
{
    return m_Messages;
}

Archiveur* Chat::getArchiveur()
{
    return m_Archiveur;
}
