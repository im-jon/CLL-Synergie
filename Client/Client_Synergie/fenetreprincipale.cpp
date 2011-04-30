#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QBoxLayout>
#include <../QScintilla/qscintilla/Qsci/qsciscintilla.h>
#include <../QScintilla/qscintilla/Qsci/qscilexercpp.h>
#include <QStringList>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QFileInfo>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    connect (Connexion::getInstance()->getMangePaquets(), SIGNAL(siNouvelleListeCollegues(QStringList*)), this, SLOT(slMiseAJourListeCollegues(QStringList*)));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::slMiseAJourListeCollegues(QStringList* noms)
{
    ui->lstCollegues->clear();

    for (int i = 0; i < noms->length(); i++) {
        AjouterCollegueListe(noms->at(i));
    }
}

void FenetrePrincipale::AjouterCollegueListe(QString nom)
{
    QListWidgetItem* item = new QListWidgetItem(QIcon(":/Icones/utilisateur.png"), nom);
    ui->lstCollegues->addItem(item);
}

void FenetrePrincipale::on_treeProjet_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    // Si la feuille n'est pas déjà ouverte.

    if (item->childCount() == 0) {

        QString extension = QFileInfo(item->text(column)).suffix();

        QsciScintilla* editeur = new QsciScintilla();
        QsciLexerCPP* lexer = new QsciLexerCPP(this);
        lexer->setFont(QFont("Monospace", 9));
        editeur->setMarginLineNumbers(1, true);
        editeur->setMarginWidth(1, 30);
        editeur->setLexer(lexer);
        editeur->setAutoIndent(true);

        ui->tabFeuilles->addTab(editeur, item->text(column));
    }
}

void FenetrePrincipale::on_tabFeuilles_currentChanged(int index)
{
    // Envoyer le paquet pour changer la feuille active.
}

void FenetrePrincipale::on_tabFeuilles_tabCloseRequested(int index)
{
    ui->tabFeuilles->removeTab(index);
}
