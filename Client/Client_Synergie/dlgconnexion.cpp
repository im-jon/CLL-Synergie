#include "dlgconnexion.h"
#include "ui_dlgconnexion.h"
#include "fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QMessageBox>
#include "clientsynergie.h"

dlgConnexion::dlgConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dlgConnexion)
{
    ui->setupUi(this);

    QSettings parametres("Moustache", "Synergie");
    parametres.beginGroup("dlgConnexion");
    ui->txtAdresse->setText(parametres.value("adresse", "127.0.0.1").toString());
    ui->txtPort->setText(parametres.value("port", 9001).toString());
    ui->txtNom->setText(parametres.value("nom", "Anonyme").toString());
    parametres.endGroup();
}

dlgConnexion::~dlgConnexion()
{
    delete ui;
}

void dlgConnexion::on_buttonBox_accepted()
{
    if (ClientSynergie::Instance()->Connecter(ui->txtAdresse->text(), ui->txtPort->text().toInt()))
    {
        ClientSynergie::Instance()->Renommer(ui->txtNom->text());
        FenetrePrincipale* w = new FenetrePrincipale(this);
        w->show();

        QSettings parametres("Moustache", "Synergie");
        parametres.beginGroup("dlgConnexion");
        parametres.setValue("adresse", ui->txtAdresse->text());
        parametres.setValue("port", ui->txtPort->text().toInt());
        parametres.setValue("nom", ui->txtNom->text());
        parametres.endGroup();

    }
    else
    {
        QMessageBox::warning(this, "Erreur de connexion", QString::fromUtf8("Incapable de rejoindre l'hôte."));
        this->show();
    }
}
