#include "dlgconnexion.h"
#include "ui_dlgconnexion.h"
#include "fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QMessageBox>

dlgConnexion::dlgConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgConnexion)
{
    ui->setupUi(this);
}

dlgConnexion::~dlgConnexion()
{
    delete ui;
}

void dlgConnexion::on_buttonBox_accepted()
{
    if (Connexion::getInstance()->Connecter(ui->txtAdresse->text(), ui->txtPort->text().toInt())) {
        FenetrePrincipale* w = new FenetrePrincipale(this);
        w->show();
    } else {
        QMessageBox::warning(this, "Erreur de connexion", "Incapable de rejoindre l'hôte.");
    }
}
