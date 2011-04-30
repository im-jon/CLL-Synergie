#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QBoxLayout>
#include <../QScintilla/qscintilla/Qsci/qsciscintilla.h>
#include <../QScintilla/qscintilla/Qsci/qscilexercpp.h>
#include <QStringList>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    connect (Connexion::getInstance()->getMangePaquets(), SIGNAL(siNouvelleListeCollegues(QStringList*)), this, SLOT(slMiseAJourListeCollegues(QStringList*)));

    m_Editeur = new QsciScintilla;
    ui->tabFeuille1->layout()->addWidget(m_Editeur);

    QsciLexerCPP* lexer = new QsciLexerCPP(this);
    lexer->setFont(QFont("Monospace", 9));
    m_Editeur->setMarginLineNumbers(1, true);
    m_Editeur->setMarginWidth(1, 30);
    m_Editeur->setLexer(lexer);
    m_Editeur->setAutoIndent(true);
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::slMiseAJourListeCollegues(QStringList* noms)
{
    ui->lstCollegues->clear();
    ui->lstCollegues->addItems(*noms);
}
