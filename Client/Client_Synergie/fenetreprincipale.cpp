#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QBoxLayout>
#include <../QScintilla/qscintilla/Qsci/qsciscintilla.h>
#include "Reseau/Paquets/paquetouvrirfichier.h"
#include <QStringList>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QFileInfo>
#include "utils.h"
#include "clientsynergie.h"

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    m_FeuillesOuvertes = new QMap<int, QsciScintilla*>();

    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siNouvelleListeCollegues(QStringList*)), this, SLOT(slMiseAJourListeCollegues(QStringList*)));
    connect (ClientSynergie::getInstance()->getMangePaquets(),SIGNAL(NouvelleListeFichiers(QStringList*)),this,SLOT(slMiseAJourListeFichiers(QStringList*)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siOuvrirFichier(int)), this, SLOT(slOuvrirFichier(int)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siNouvelleDonnees(int, QString)), this, SLOT(slNouvelleDonnees(int, QString)));
    connect (this, SIGNAL(InsertionTexte(int,int,QString)), ClientSynergie::getInstance(), SLOT(slOnInsertionTexte(int,int,QString)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siNouveauTexte(int,int,QString)), this, SLOT(slNouveauTexte(int,int,QString)));
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
    if (item->childCount() == 0) {
        int id = ClientSynergie::getInstance()->TrouverFichierParNom(item->text(column));
        if (!m_FeuillesOuvertes->contains(id)) {
            ClientSynergie::getInstance()->getConnexion()->EnvoyerPaquet(new PaquetOuvrirFichier(id));
        } else {
            int index = ui->tabFeuilles->indexOf(m_FeuillesOuvertes->value(id));
            ui->tabFeuilles->setCurrentIndex(index);
        }
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
    if (ui->tabFeuilles->count() > 1) {
        m_FeuillesOuvertes->remove(m_FeuillesOuvertes->key((QsciScintilla*)ui->tabFeuilles->widget(index)));
        ui->tabFeuilles->removeTab(index);
    }
}

void FenetrePrincipale::slOuvrirFichier(int id)
{
    QString fichier = ClientSynergie::getInstance()->TrouverFichierParID(id);
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

    int index = ui->tabFeuilles->addTab(editeur, fichier);
    ui->tabFeuilles->setCurrentIndex(index);
    m_FeuillesOuvertes->insert(id, editeur);
    connect(editeur,SIGNAL(textInserted(int,QString)),this,SLOT(slInsertionTexte(int,QString)));
}

void FenetrePrincipale::slNouvelleDonnees(int id, QString contenu)
{
    m_FeuillesOuvertes->value(id)->append(contenu, true);
}

void FenetrePrincipale::slInsertionTexte(int Position,QString Texte)
{
    int id = m_FeuillesOuvertes->key((QsciScintilla*)ui->tabFeuilles->currentWidget());

    emit(InsertionTexte(id,Position,Texte));
}

QsciScintilla* FenetrePrincipale::ChercherEditeurParID(int id)
{
    return m_FeuillesOuvertes->value(id);
}

void FenetrePrincipale::slNouveauTexte(int id,int position, QString texte)
{
    qDebug() << "ID: " << id << " Texte: " << texte;
    ChercherEditeurParID(id)->insertAtPos(texte, position, true);
}
