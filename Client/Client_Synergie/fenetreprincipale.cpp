#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QBoxLayout>
#include <../QScintilla/qscintilla/Qsci/qsciscintilla.h>
#include <QStringList>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QFileInfo>
#include "utils.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    m_Onglets = new QMap<int, int>();

    connect (Connexion::getInstance()->getMangePaquets(), SIGNAL(siNouvelleListeCollegues(QStringList*)), this, SLOT(slMiseAJourListeCollegues(QStringList*)));
    connect (Connexion::getInstance()->getMangePaquets(),SIGNAL(NouvelleListeFichiers(QStringList*)),this,SLOT(slMiseAJourListeFichiers(QStringList*)));
    connect (Connexion::getInstance()->getMangePaquets(), SIGNAL(siOuvrirFichier(int,QString)), this, SLOT(slOuvrirFichier(int,QString)));
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

void FenetrePrincipale::slMiseAJourListeFichiers(QStringList* fichiers)
{
    ui->treeProjet->clear();

    for (int i = 0; i < fichiers->length(); i++) {
        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, fichiers->at(i));
        ui->treeProjet->addTopLevelItem(item);
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

    }
}

void FenetrePrincipale::on_tabFeuilles_currentChanged(int index)
{
    QsciLexer* lexer = ((QsciScintilla*)ui->tabFeuilles->currentWidget())->lexer();
    if (lexer) {
        ui->lblLangage->setText(lexer->language());
    }

    // Envoyer le paquet pour changer la feuille active.
}

void FenetrePrincipale::on_tabFeuilles_tabCloseRequested(int index)
{
    ui->tabFeuilles->removeTab(index);
}

void FenetrePrincipale::slOuvrirFichier(int id, QString contenu)
{
    QString fichier = Connexion::getInstance()->getFichiers()->key(id);
    QString extension = QFileInfo(fichier).suffix();

    QsciScintilla* editeur = new QsciScintilla();
    editeur->setMarginLineNumbers(1, true);
    editeur->setMarginWidth(1, 30);

    QsciLexer* lexer = Utils::TrouverLexer(extension);
    if (lexer) {
        editeur->setLexer(lexer);
        editeur->lexer()->setFont(QFont("Monospace", 9));
    }
    editeur->setAutoIndent(true);
    editeur->setText(contenu);

    int index = ui->tabFeuilles->addTab(ui->tabFeuilles, fichier);
    ui->tabFeuilles->setCurrentIndex(index);
    m_Onglets->insert(id, index);
}
