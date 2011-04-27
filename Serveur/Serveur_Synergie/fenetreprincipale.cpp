#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Console/console.h"
#include <QDebug>
#include "serveursynergie.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    connect (Console::Instance(), SIGNAL(siSortie(QString)), this, SLOT(sl_Console_Sortie(QString)));
    connect (Console::Instance(), SIGNAL(siVider()), this, SLOT(sl_Console_Vider()));

    ServeurSynergie::getInstance()->Demarrer();
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::on_txtEntree_returnPressed()
{
    Console::Instance()->Ecrire(ui->txtEntree->text());
    ui->txtEntree->clear();
}

void FenetrePrincipale::sl_Console_Sortie(QString ligne)
{
    ui->txtSortie->append(ligne);
}

void FenetrePrincipale::sl_Console_Vider()
{
    ui->txtSortie->clear();
}
