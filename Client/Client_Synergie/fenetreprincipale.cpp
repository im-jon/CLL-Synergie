#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QBoxLayout>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    m_Editeur = new QsciScintilla();
    ui->tab->layout()->addWidget(m_Editeur);
    m_Editeur->setMarginLineNumbers(1, true);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}
