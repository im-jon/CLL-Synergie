#include "mangepaquetclient.h"
#include <QDataStream>
#include <QDebug>
#include <QStringList>
#include "connexion.h"

MangePaquetClient::MangePaquetClient(QObject *parent) :
    QObject(parent)
{
}

void MangePaquetClient::Interpreter(QDataStream* stream)
{
    quint8 id;

    *stream >> id;

    switch (id) {
    case 1:
        qDebug();
        Reception_ListeCollegues(stream);
        break;
    case 2:
        Reception_ListeDesFichiers(stream);
        break;
    case 10:
        Reception_OuvertureFichier(stream);
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

    for(int i = 0; i < nombre; i++)
    {
        int id;
        *stream >> id;
        QString nom;
        *stream >> nom;
        fichiers->append(nom);
        Connexion::getInstance()->getFichiers()->insert(nom, id);
    }
    emit(NouvelleListeFichiers(fichiers));
}

void MangePaquetClient::Reception_OuvertureFichier(QDataStream *stream)
{
    int id;
    *stream >> id;
    QString texte;
    *stream >> texte;

    emit(siOuvrirFichier(id, texte));
}
