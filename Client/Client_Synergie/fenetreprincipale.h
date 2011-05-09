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

    QsciScintilla* getEditeur(int id);
    QsciScintilla* getEditeur(Feuille* feuille);

private:
    void AjouterCollegue(Collegue* collegue);
    void AjouterFeuille(Feuille* feuille);

    Ui::FenetrePrincipale *ui;
    QMap<Collegue*, QListWidgetItem*>* m_Collegues;
    QMap<Feuille*, QTreeWidgetItem*>* m_Feuilles;
    QMap<Feuille*, QsciScintilla*>* m_FeuillesOuvertes;


private slots:
    void on_treeProjet_itemDoubleClicked(QTreeWidgetItem* item, int column);
    void on_tabFeuilles_currentChanged(int index);
    void on_tabFeuilles_tabCloseRequested(int index);
    void slInsertionTexteEditeur(int position, QString texte);
    void slEffacementTexteEditeur(int pos, int longeur);

    void slConnexionCollegues(Collegue* collegue);
    void slDeconnexionCollegues(Collegue* collegue);
    void slAjoutFeuille(Feuille* feuille);
    void slOuvrirFichier(int id);
    void slNouvelleDonnees(int id, QString contenu);
    void slInsertionTexteServeur(int id, int position, QString texte);
    void slEffacementTexteServeur(int id, int position, int longeur);
    void slMessageChat(Collegue* collegue, QString message);
    void slCheckSum(int id, int longueur);

    void on_txtLigneConv_returnPressed();

signals :
    void siInsertionTexte(int,int,QString);
    void siEffacementTexte(int id, int pos, int longeur);
    void siEnvoiTexteChat(QString);
    void siReponseCheckSum(int id);

};

#endif // FENETREPRINCIPALE_H
