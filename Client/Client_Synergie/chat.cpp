#include "chat.h"
#include "clientsynergie.h"
#include "Reseau/Paquets/paquetenvoichat.h"

Chat::Chat(QObject *parent) :
    QObject(parent)
{
}

void Chat::slEnvoyer(QString message)
{
    if (!message.isEmpty())
    {
        ClientSynergie::Instance()->getConnexion()->EnvoyerPaquet(new PaquetEnvoiChat(message));
    }
}

void Chat::MessageRecu(Collegue* auteur, QString message)
{
    emit (siMessageRecu(auteur, message));
}
