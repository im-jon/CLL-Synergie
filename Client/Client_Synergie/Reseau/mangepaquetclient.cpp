#include "mangepaquetclient.h"
#include <QDataStream>
#include <QDebug>
#include <QStringList>
#include "connexion.h"
#include "clientsynergie.h"
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
    switch (id) {
    case 1:
        Reception_ListeCollegues(stream);
        break;
    case 2:
        Reception_ListeDesFichiers(stream);
        break;
    case 10:
        Reception_OuvertureFichier(stream);
        break;
    case 15:
        Reception_Donnees(stream);
        break;
    case 5:
        Reception_Texte(stream);
        break;
    default:
        qDebug() << "Réception d'un paquet inconnu #" << id;
        break;
    }
}

void MangePaquetClient::Reception_ListeCollegues(QDataStream* stream)
{
    QStringList* collegues = new QStringList();
    int nombre;

    *stream >> nombre;

    for(int i = 0; i < nombre; i++) {
        QString nom;
        *stream >> nom;
        collegues->append(nom);
    }

    emit (siNouvelleListeCollegues(collegues));
}

void MangePaquetClient::Reception_ListeDesFichiers(QDataStream* stream)
{
    QStringList* fichiers = new QStringList();
    int nombre;

    *stream >> nombre;

    for(int i = 0; i < nombre; i++) {
        int id;
        *stream >> id;
        QString nom;
        *stream >> nom;
        fichiers->append(nom);
        ClientSynergie::getInstance()->AjouterFichier(nom, id);
    }
    emit(NouvelleListeFichiers(fichiers));
}

void MangePaquetClient::Reception_OuvertureFichier(QDataStream *stream)
{
    int id;
    *stream >> id;

    emit(siOuvrirFichier(id));
}

void MangePaquetClient::Reception_Donnees(QDataStream *stream)
{
    int id;
    *stream >> id;

    QString donnees;
    *stream >> donnees;
    ClientSynergie::getInstance()->getConnexion()->EnvoyerPaquet(new PaquetReceptionDonnees(id));

    emit(siNouvelleDonnees(id, donnees));
}

void MangePaquetClient::Reception_Texte(QDataStream *stream)
{
    int id;
    *stream >>id;
    int position;
    *stream >> position;
    QString Texte;
    *stream >> Texte;

    emit (siNouveauTexte(id,position,Texte));

}

void MangePaquetClient::Reception_EffacementTexte(QDataStream *stream)
{
    int id;
    *stream >> id;
    int position;
    *stream >> position;
    int longeur;
    *stream >> longeur;

    emit (siEffacementTexte(id, position, longeur));
}
