#include "chat.h"
#include "Reseau/Paquets/paquetmessagechat.h"

Chat::Chat(QObject *parent) :
    QObject(parent)
{
}

void Chat::NouveauMessage(Client *auteur, QString message)
{
    Serveur::Instance()->getClients()->EnvoyerPaquetATous(
                new PaquetMessageChat(auteur, message),
                auteur);
}
