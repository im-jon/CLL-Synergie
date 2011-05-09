#ifndef DEPAQUETEUR_H
#define DEPAQUETEUR_H

#include <QObject>
#include <QMap>
#include "collegue.h"

class Depaqueteur : public QObject
{
    Q_OBJECT
public:
    explicit Depaqueteur(QObject* parent = 0);
    void Interpreter(QDataStream&);

private:
    void Reception_ListeCollegues(QDataStream& stream);
    void Reception_ListeFichiers(QDataStream& stream);
    void Reception_ConnexionCollegue(QDataStream& stream);
    void Reception_DeconnexionCollegue(QDataStream& stream);
    void Reception_OuvertureFichier(QDataStream& stream);
    void Reception_Donnees(QDataStream& stream);
    void Reception_Texte(QDataStream& stream);
    void Reception_EffacementTexte(QDataStream& stream);
    void Reception_MessageChat(QDataStream& stream);
    void Reception_CheckSum(QDataStream& stream);
    void Reception_Nettoyer(QDataStream& stream);

signals:
    void siListeCollegues(QStringList* noms);
    void siListeFichiers(QStringList* noms);
    void siOuvrirFichier(int id);
    void siDonnees(int id, QString donnees);
    void siInsertionTexte(int id, int position, QString texte);
    void siEffacementTexte(int id, int position, int longeur);
    void siMessageChat(Collegue* collegue, QString message);
    void siCheckSum(int id,int longueur);
    void siNettoyer(int id);

public slots:
};

#endif // DEPAQUETEUR_H
