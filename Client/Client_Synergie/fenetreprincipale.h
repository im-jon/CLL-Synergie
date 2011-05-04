#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QMap>
#include <QList>
#include <qtabbar.h>

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
    void AjouterCollegueListe(QString nom);
    QsciScintilla* ChercherEditeurParID(int id);

private:
    Ui::FenetrePrincipale *ui;
    QMap<int, QsciScintilla*>* m_FeuillesOuvertes;


private slots:

    void on_treeProjet_itemDoubleClicked(QTreeWidgetItem* item, int column);

    void on_tabFeuilles_currentChanged(int index);

    void on_tabFeuilles_tabCloseRequested(int index);

public slots:
    void slMiseAJourListeCollegues(QStringList* noms);
    void slMiseAJourListeFichiers(QStringList* fichiers);
    void slOuvrirFichier(int id);
    void slNouvelleDonnees(int id, QString contenu);
    void slInsertionTexte(int,QString);
    void slNouveauTexte(int,int,QString);
    void slEffacementTexteEditeur(int pos, int longeur);
    void slEffacementTexteServeur(int id, int position, int longeur);

signals :
    void InsertionTexte(int,int,QString);
    void EffacementTexte(int id, int pos, int longeur);

};

#endif // FENETREPRINCIPALE_H
