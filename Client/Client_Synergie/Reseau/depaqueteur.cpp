#include "depaqueteur.h"
#include <QDataStream>
#include <QDebug>
#include <QStringList>
#include "connexion.h"
#include "clientsynergie.h"
#include "collegue.h"
#include "Paquets/paquetreceptiondonnees.h"

Depaqueteur::Depaqueteur(QObject *parent) :
    QObject(parent)
{
}

void Depaqueteur::Interpreter(QDataStream& stream)
{
    quint8 id;

    stream >> id;

    switch (id)
    {
        case 1:
            Reception_ListeCollegues(stream);
            break;
        case 2:
            Reception_ListeFichiers(stream);
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
            Reception_MessageChat(stream);
            break;
        default:
            qDebug() << "Réception d'un paquet inconnu #" << id;
            break;
    }
}

void Depaqueteur::Reception_ListeCollegues(QDataStream& stream)
{
    int nombre;

    stream >> nombre;

    for (int i = 0; i < nombre; i++)
    {
        int id;
        QString nom;

        stream >> id;
        stream >> nom;

        ClientSynergie::Instance()->ConnexionCollegue(new Collegue(id, nom, this));
    }
}

void Depaqueteur::Reception_ListeFichiers(QDataStream& stream)
{
    int nombre;

    stream >> nombre;

    for (int i = 0; i < nombre; i++)
    {
        int id;
        QString nom;

        stream >> id;
        stream >> nom;

        ClientSynergie::Instance()->AjouterFeuille(nom, id);
    }
}

void Depaqueteur::Reception_ConnexionCollegue(QDataStream& stream)
{
    int id;
    QString nom;

    stream >> id;
    stream >> nom;

    ClientSynergie::Instance()->ConnexionCollegue(new Collegue(id, nom, this));
}

void Depaqueteur::Reception_DeconnexionCollegue(QDataStream& stream)
{
    int id;

    stream >> id;

    ClientSynergie::Instance()->DeconnexionCollegue(id);
}

void Depaqueteur::Reception_OuvertureFichier(QDataStream& stream)
{
    int id;

    stream >> id;

    emit (siOuvrirFichier(id));
}

void Depaqueteur::Reception_Donnees(QDataStream& stream)
{
    int id;
    QString donnees;

    stream >> id;
    stream >> donnees;

    ClientSynergie::Instance()->getConnexion()->EnvoyerPaquet(new PaquetReceptionDonnees(id));

    emit(siDonnees(id, donnees));
}

void Depaqueteur::Reception_Texte(QDataStream& stream)
{
    int id;
    int position;
    QString texte;

    stream >> id;
    stream >> position;
    stream >> texte;

    emit (siInsertionTexte(id, position, texte));

}

void Depaqueteur::Reception_EffacementTexte(QDataStream& stream)
{
    int id;
    int position;
    int longeur;

    stream >> id;
    stream >> position;
    stream >> longeur;

    emit (siEffacementTexte(id, position, longeur));
}

void Depaqueteur::Reception_MessageChat(QDataStream& stream)
{
    int id;
    QString message;

    stream >> id;
    stream >> message;

    Collegue* collegue = ClientSynergie::Instance()->getCollegue(id);

    emit (siMessageChat(collegue, message));
}
