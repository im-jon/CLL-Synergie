#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include <QTreeWidgetItem>

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

private:
    Ui::FenetrePrincipale *ui;

private slots:

    void on_treeProjet_itemDoubleClicked(QTreeWidgetItem* item, int column);

    void on_tabFeuilles_currentChanged(int index);

    void on_tabFeuilles_tabCloseRequested(int index);

public slots:
    void slMiseAJourListeCollegues(QStringList* noms);

};

#endif // FENETREPRINCIPALE_H
