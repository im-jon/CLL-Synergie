#include "depaqueteur.h"
#include <QDataStream>
#include <QDebug>
#include <QColor>
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

    qDebug() << id;

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
            Reception_InsertionTexte(stream);
            break;
        case 7:
            Reception_EffacementTexte(stream);
            break;
        case 10:
            Reception_OuvertureFeuille(stream);
            break;
        case 13:
            Reception_Verification(stream);
            break;
        case 15:
            Reception_Donnees(stream);
            break;
        case 16:
            Reception_MessageChat(stream);
            break;
        case 17:
            Reception_Nettoyer(stream);
            break;
        case 18:
            Reception_FermetureServeur(stream);
            break;
        case 19:
            Reception_CollegueOuvertureFeuille(stream);
            break;
        case 20:
            Reception_CollegueFermetureFeuille(stream);
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
        QColor couleur;

        stream >> id;
        stream >> nom;
        stream >> couleur;

        ClientSynergie::Instance()->ConnexionCollegue(new Collegue(id, nom, couleur, this));
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
    QColor couleur;

    stream >> id;
    stream >> nom;
    stream >> couleur;

    ClientSynergie::Instance()->ConnexionCollegue(new Collegue(id, nom, couleur, this));
}

void Depaqueteur::Reception_DeconnexionCollegue(QDataStream& stream)
{
    int id;

    stream >> id;

    ClientSynergie::Instance()->DeconnexionCollegue(id);
}

void Depaqueteur::Reception_OuvertureFeuille(QDataStream& stream)
{
    int id;
    int nombre;

    stream >> id;
    stream >> nombre;

    emit siOuvrirFichier(id);

    int idCollegue;
    int position;
    Collegue* collegue;
    for (int i = 0; i < nombre; i++)
    {

        stream >> idCollegue;
        stream >> position;

        collegue = ClientSynergie::Instance()->getCollegue(idCollegue);

        emit siCollegueOuvertureFeuille(collegue, id, position);
    }
}

void Depaqueteur::Reception_Donnees(QDataStream& stream)
{
    int id;
    QString donnees;

    stream >> id;
    stream >> donnees;

    ClientSynergie::Instance()->getConnexion()->EnvoyerPaquet(new PaquetReceptionDonnees(id));

    emit siDonnees(id, donnees);
}

void Depaqueteur::Reception_InsertionTexte(QDataStream& stream)
{
    int idAuteur;
    int idFeuille;
    int position;
    QString texte;

    stream >> idAuteur;
    stream >> idFeuille;
    stream >> position;
    stream >> texte;

    emit siInsertionTexte(idAuteur, idFeuille, position, texte);
}

void Depaqueteur::Reception_EffacementTexte(QDataStream& stream)
{
    int idAuteur;
    int idFeuille;
    int position;
    int longeur;

    stream >> idAuteur;
    stream >> idFeuille;
    stream >> position;
    stream >> longeur;

    emit siEffacementTexte(idAuteur, idFeuille, position, longeur);
}

void Depaqueteur::Reception_MessageChat(QDataStream& stream)
{
    int id;
    QString message;

    stream >> id;
    stream >> message;

    Collegue* collegue = ClientSynergie::Instance()->getCollegue(id);

    ClientSynergie::Instance()->getChat()->MessageRecu(collegue, message);
}

void Depaqueteur::Reception_Verification(QDataStream& stream)
{
    int id;
    int longueur;

    stream >> id;
    stream >> longueur;

    emit siVerification(id, longueur);
}

void Depaqueteur::Reception_Nettoyer(QDataStream &stream)
{
    int id;

    stream >> id;

    emit siNettoyer(id);
}

void Depaqueteur::Reception_FermetureServeur(QDataStream &stream)
{
    emit siFermetureServeur();
}

void Depaqueteur::Reception_CollegueOuvertureFeuille(QDataStream& stream)
{
    int idCollegue;
    int idFeuille;

    stream >> idCollegue;
    stream >> idFeuille;

    Collegue* collegue = ClientSynergie::Instance()->getCollegue(idCollegue);

    emit siCollegueOuvertureFeuille(collegue, idFeuille, -1);
}

void Depaqueteur::Reception_CollegueFermetureFeuille(QDataStream &stream)
{
    int idCollegue;
    int idFeuille;

    stream >> idCollegue;
    stream >> idFeuille;

    emit siCollegueFermetureFeuille(idCollegue, idFeuille);
}
