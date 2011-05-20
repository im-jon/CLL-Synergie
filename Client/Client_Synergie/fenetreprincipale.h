#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QListWidgetItem>
#include <QMap>
#include <QList>
#include <qtabbar.h>
#include "collegue.h"
#include "feuille.h"

class QsciScintilla;
class QsciLexer;

namespace Ui {
    class FenetrePrincipale;
}

class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

public:
    explicit FenetrePrincipale(QWidget *parent = 0);
    ~FenetrePrincipale();

    QsciScintilla* getEditeur(int idFeuille);
    QsciScintilla* getEditeur(Feuille* feuille);


private:
    void Fermer();
    void AjouterCollegue(Collegue* collegue);
    void AjouterFeuille(Feuille* feuille);
    void laverListeCollegues();
    void MAJPositionListeCollegue(QsciScintilla* editeur, Collegue* collegue, int position);

    Ui::FenetrePrincipale *ui;
    QMap<Collegue*, QListWidgetItem*>* m_Collegues;
    QMap<Feuille*, QTreeWidgetItem*>* m_Feuilles;
    QMap<Feuille*, QsciScintilla*>* m_FeuillesOuvertes;


private slots:
    void on_treeProjet_itemDoubleClicked(QTreeWidgetItem* item, int column);
    void on_tabFeuilles_currentChanged(int index);
    void on_tabFeuilles_tabCloseRequested(int index);
    void on_txtLigneConv_returnPressed();

    void slInsertionTexteEditeur(int position, QString texte);
    void slEffacementTexteEditeur(int position, int longeur);
    void slLignesChangeesEditeur();
    void slChangementTexteEditeur();

    void slInsertionTexteServeur(int idCollegue, int idFeuille, int position, QString texte);
    void slEffacementTexteServeur(int idAuteur, int idFeuille, int position, int longeur);

    void slAjoutFeuille(Feuille* feuille);
    void slOuvrirFeuille(int idFeuille);

    void slNettoyerFeuille(int idFeuille);
    void slNouvelleDonnees(int idFeuille, QString contenu);
    void slVerification(int idFeuille, int longueur);

    void slConnexionCollegues(Collegue* collegue);
    void slDeconnexionCollegues(Collegue* collegue);

    void slCollegueOuvertureFeuille(Collegue* collegue, int idFeuille, int position);
    void slCollegueFermetureFeuille(int idCollegue, int idFeuille);

    void slMessageChat(Collegue* collegue, QString message);
    void slMessageGeneral(QString message);

    void slFermetureServeur();

    void on_actionCopier_triggered();
    void on_actionColler_triggered();
    void on_actionCouper_triggered();
    void on_actionEffacer_triggered();
    void on_actionAnnuler_triggered();
    void on_actionRevenir_triggered();
    void on_actionSe_d_connecter_triggered();
    void on_actionQuitter_triggered();
    void on_actionAutoCompletion_triggered();


signals :
    void siInsertionTexte(int idFeuille, int position, QString texte);
    void siEffacementTexte(int idFeuille, int position, int longeur);

    void siFermerFeuille(int idFeuille);
    void siVerification(int idFeuille, bool reponse);

    void siEnvoiTexteChat(QString);

};

#endif // FENETREPRINCIPALE_H
