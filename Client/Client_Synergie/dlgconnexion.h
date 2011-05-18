#ifndef DLGCONNEXION_H
#define DLGCONNEXION_H

#include <QDialog>
#include <QSettings>
#include <QColorDialog>

namespace Ui {
    class dlgConnexion;
}

class dlgConnexion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgConnexion(QWidget *parent = 0);
    ~dlgConnexion();

private:
    Ui::dlgConnexion *ui;
    QColor m_Couleur;
    void MAJBoutonCouleur();

private slots:
    void on_buttonBox_accepted();
    void on_btnCouleur_clicked();
    void slCouleurChoisie(QColor couleur);
};

#endif // DLGCONNEXION_H
