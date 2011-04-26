#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H

#include <QMainWindow>

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

private slots:
    void on_txtEntree_returnPressed();
    void sl_Console_Sortie(QString ligne);
    void sl_Console_Vider();
};

#endif // FENETREPRINCIPALE_H
