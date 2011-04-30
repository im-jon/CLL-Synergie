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
    QsciLexerCPP* lexer = new QsciLexerCPP(this);
    lexer->setFont(QFont("Monospace", 9));
    ui->tabFeuille1->layout()->addWidget(m_Editeur);

    m_Editeur->setMarginLineNumbers(1, true);
    m_Editeur->setMarginWidth(1, 30);
    m_Editeur->setLexer(lexer);
    m_Editeur->setAutoIndent(true);
    m_Editeur->setCallTipsVisible(1);

    connect (m_Editeur, SIGNAL(cursorPositionChanged(int,int)), this, SLOT(slCurseurBouger(int,int)));
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

void FenetrePrincipale::slCurseurBouger(int x, int y)
{
    m_Editeur->autoCompleteFromAll();
}
