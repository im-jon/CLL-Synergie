#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Reseau/connexion.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    connect(ui->btnConnection,SIGNAL(clicked()),this,SLOT(OnClicked()));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::OnClicked()
{
    Connexion::getInstance()->Connecter("127.0.0.1",9001);
}
