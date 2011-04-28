#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>
#include "../QScintilla/qscintilla/Qsci/qsciscintilla.h"

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
    void OnClicked();
};

#endif // FENETREPRINCIPALE_H
