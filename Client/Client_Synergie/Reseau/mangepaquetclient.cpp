#include "mangepaquetclient.h"
#include <QDataStream>
#include <QDebug>
#include <QStringList>
#include "connexion.h"
#include "clientsynergie.h"
#include "collegue.h"
#include "Paquets/paquetreceptiondonnees.h"

MangePaquetClient::MangePaquetClient(QObject *parent) :
    QObject(parent)
{
}

void MangePaquetClient::Interpreter(QDataStream* stream)
{
    quint8 id;

    *stream >> id;
    qDebug() << id;
    switch (id)
    {
        case 1:
            Reception_ListeCollegues(stream);
            break;
        case 2:
            Reception_ListeDesFichiers(stream);
            break;
        case 3:
            Reception_ConnexionCollegue(stream);
            break;
        case 4:
            Reception_DeconnexionCollegue(stream);
            break;
        case 5:
            Reception_Texte(stream);
            break;
        case 7:
            Reception_EffacementTexte(stream);
            break;
        case 10:
            Reception_OuvertureFichier(stream);
            break;
        case 15:
            Reception_Donnees(stream);
            break;
        case 16:
            Reception_TexteChat(stream);
            break;
        default:
            qDebug() << "Réception d'un paquet inconnu #" << id;
            break;
    }
}

void MangePaquetClient::Reception_ListeCollegues(QDataStream* stream)
{
    int nombre;

    *stream >> nombre;

    for(int i = 0; i < nombre; i++)
    {
        int id;
        QString nom;

        *stream >> id;
        *stream >> nom;

        ClientSynergie::getInstance()->ConnexionCollegue(new Collegue(id, nom, this));
    }


}

void MangePaquetClient::Reception_ListeDesFichiers(QDataStream* stream)
{
    QStringList* fichiers = new QStringList;
    int nombre;

    *stream >> nombre;

    for(int i = 0; i < nombre; i++)
    {
        int id;
        QString nom;

        *stream >> id;
        *stream >> nom;

        fichiers->append(nom);
        ClientSynergie::getInstance()->AjouterFichier(nom, id);
    }

    emit (siNouvelleListeFichiers(fichiers));
}

void MangePaquetClient::Reception_ConnexionCollegue(QDataStream *stream)
{
    int id;
    QString nom;

    *stream >> id;
    *stream >> nom;

    ClientSynergie::getInstance()->ConnexionCollegue(new Collegue(id, nom, this));
}

void MangePaquetClient::Reception_DeconnexionCollegue(QDataStream *stream)
{
    int id;
    *stream >> id;

    ClientSynergie::getInstance()->DeconnexionCollegue(id);
}

void MangePaquetClient::Reception_OuvertureFichier(QDataStream *stream)
{
    int id;
    *stream >> id;

    emit (siOuvrirFichier(id));
}

void MangePaquetClient::Reception_Donnees(QDataStream *stream)
{
    int id;
    QString donnees;

    *stream >> id;
    *stream >> donnees;

    ClientSynergie::getInstance()->getConnexion()->EnvoyerPaquet(new PaquetReceptionDonnees(id));

    emit(siNouvelleDonnees(id, donnees));
}

void MangePaquetClient::Reception_Texte(QDataStream *stream)
{
    int id;
    int position;
    QString texte;

    *stream >>id;
    *stream >> position;
    *stream >> texte;

    emit (siNouveauTexte(id, position, texte));

}

void MangePaquetClient::Reception_EffacementTexte(QDataStream *stream)
{
    int id;
    int position;
    int longeur;

    *stream >> id;
    *stream >> position;
    *stream >> longeur;

    emit (siEffacementTexte(id, position, longeur));
}

void MangePaquetClient::Reception_TexteChat(QDataStream *stream)
{
    int id;
    QString message;

    *stream >> id;
    *stream >> message;

    Collegue* collegue = ClientSynergie::getInstance()->TrouverCollegueParID(id);

    emit (siNouveauTexteChat(collegue, message));
}
