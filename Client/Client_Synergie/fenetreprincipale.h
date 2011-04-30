#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>

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

private:
    Ui::FenetrePrincipale *ui;
    QsciScintilla* m_Editeur;

private slots:
    void slCurseurBouger(int, int);

public slots:
    void slMiseAJourListeCollegues(QStringList* noms);

};

#endif // FENETREPRINCIPALE_H
