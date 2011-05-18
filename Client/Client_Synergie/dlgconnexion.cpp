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
    QColor couleurAleatoire = QColor(qrand() % 255, qrand() % 255, qrand() % 255);
    m_Couleur = parametres.value("couleur", couleurAleatoire).value<QColor>();
    parametres.endGroup();

    MAJBoutonCouleur();
}

dlgConnexion::~dlgConnexion()
{
    delete ui;
}

void dlgConnexion::on_buttonBox_accepted()
{
    if (ClientSynergie::Instance()->Connecter(ui->txtAdresse->text(), ui->txtPort->text().toInt()))
    {
        ClientSynergie::Instance()->setNom(ui->txtNom->text());
        ClientSynergie::Instance()->setCouleur(m_Couleur);
        ClientSynergie::Instance()->Authentifier();

        FenetrePrincipale* w = new FenetrePrincipale(this);
        w->show();

        QSettings parametres("Moustache", "Synergie");
        parametres.beginGroup("dlgConnexion");
        parametres.setValue("adresse", ui->txtAdresse->text());
        parametres.setValue("port", ui->txtPort->text().toInt());
        parametres.setValue("nom", ui->txtNom->text());
        parametres.setValue("couleur", m_Couleur);
        parametres.endGroup();

    }
    else
    {
        QMessageBox::warning(this, "Erreur de connexion", QString::fromUtf8("Incapable de rejoindre l'hôte."));
        this->show();
    }
}

void dlgConnexion::on_btnCouleur_clicked()
{
    QColorDialog* dialogue = new QColorDialog(m_Couleur, this);
    dialogue->open(this, SLOT(slCouleurChoisie(QColor)));
}

void dlgConnexion::slCouleurChoisie(QColor couleur)
{
    m_Couleur = couleur;
    MAJBoutonCouleur();
}

void dlgConnexion::MAJBoutonCouleur()
{
    QString ligne = QString("QPushButton { background-color: rgb(%1,%2,%3); }")
            .arg(m_Couleur.red()).arg(m_Couleur.green()).arg(m_Couleur.blue());
    ui->btnCouleur->setStyleSheet(ligne);
}
