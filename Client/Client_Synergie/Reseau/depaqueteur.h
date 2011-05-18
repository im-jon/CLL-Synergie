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
    void Reception_OuvertureFeuille(QDataStream& stream);
    void Reception_Donnees(QDataStream& stream);
    void Reception_InsertionTexte(QDataStream& stream);
    void Reception_EffacementTexte(QDataStream& stream);
    void Reception_MessageChat(QDataStream& stream);
    void Reception_Verification(QDataStream& stream);
    void Reception_Nettoyer(QDataStream& stream);
    void Reception_CollegueOuvertureFeuille(QDataStream& stream);
    void Reception_CollegueFermetureFeuille(QDataStream& stream);

signals:
    void siListeCollegues(QStringList* noms);
    void siListeFichiers(QStringList* noms);
    void siOuvrirFichier(int id);
    void siDonnees(int id, QString donnees);
    void siInsertionTexte(int idAuteur, int idFeuille, int position, QString texte);
    void siEffacementTexte(int idAuteur, int idFeuille, int position, int longeur);
    void siVerification(int id, int longueur);
    void siNettoyer(int id);
    void siCollegueOuvertureFeuille(Collegue* collegue, int idFeuille, int position);
    void siCollegueFermetureFeuille(int idCollegue, int idFeuille);

public slots:
};

#endif // DEPAQUETEUR_H
