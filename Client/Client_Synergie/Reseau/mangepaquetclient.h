#ifndef MANGEPAQUETCLIENT_H
#define MANGEPAQUETCLIENT_H

#include <QObject>
#include <QMap>
#include "collegue.h"

class MangePaquetClient : public QObject
{
    Q_OBJECT
public:
    explicit MangePaquetClient(QObject *parent = 0);
    void Interpreter(QDataStream*);

private:
    void Reception_ListeCollegues(QDataStream* stream);
    void Reception_ListeFichiers(QDataStream* stream);
    void Reception_ConnexionCollegue(QDataStream* stream);
    void Reception_DeconnexionCollegue(QDataStream* stream);
    void Reception_OuvertureFichier(QDataStream* stream);
    void Reception_Donnees(QDataStream* stream);
    void Reception_Texte(QDataStream* stream);
    void Reception_EffacementTexte(QDataStream* stream);
    void Reception_MessageChat(QDataStream* stream);

signals:
    void siListeCollegues(QStringList* noms);
    void siListeFichiers(QStringList* noms);
    void siOuvrirFichier(int id);
    void siDonnees(int id, QString donnees);
    void siInsertionTexte(int id, int position, QString texte);
    void siEffacementTexte(int id, int position, int longeur);
    void siMessageChat(Collegue* collegue, QString message);

public slots:
};

#endif // MANGEPAQUETCLIENT_H
