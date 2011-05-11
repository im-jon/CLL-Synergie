#include "fenetreprincipale.h"
#include "ui_fenetreprincipale.h"
#include "Reseau/connexion.h"
#include <QBoxLayout>
#include <../QScintilla/qscintilla/Qsci/qsciscintilla.h>
#include "Reseau/Paquets/paquetouvrirfeuille.h"
#include <QStringList>
#include <QListWidgetItem>
#include <QTreeWidgetItem>
#include <QFileInfo>
#include "utils.h"
#include "clientsynergie.h"
#include <QList>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    m_Collegues = new QMap<Collegue*, QListWidgetItem*>;
    m_Feuilles = new QMap<Feuille*, QTreeWidgetItem*>;
    m_FeuillesOuvertes = new QMap<Feuille*, QsciScintilla*>;

    connect (ClientSynergie::Instance(), SIGNAL(siConnexionCollegue(Collegue*)), this, SLOT(slConnexionCollegues(Collegue*)));
    connect (ClientSynergie::Instance(), SIGNAL(siDeconnexionCollegue(Collegue*)), this, SLOT(slDeconnexionCollegues(Collegue*)));
    connect (ClientSynergie::Instance(), SIGNAL(siAjoutFeuille(Feuille*)), this, SLOT(slAjoutFeuille(Feuille*)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siOuvrirFichier(int)), this, SLOT(slOuvrirFichier(int)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siDonnees(int, QString)), this, SLOT(slNouvelleDonnees(int, QString)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siInsertionTexte(int, int, QString)), this, SLOT(slInsertionTexteServeur(int, int, QString)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siEffacementTexte(int, int, int)), this, SLOT(slEffacementTexteServeur(int, int, int)));
    connect (ClientSynergie::Instance()->getChat(), SIGNAL(siMessageRecu(Collegue*,QString)), this, SLOT(slMessageChat(Collegue*, QString)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siVerification(int, int)), this, SLOT(slVerification(int,int)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siNettoyer(int)), this,SLOT(slNettoyer(int)));


    connect (this, SIGNAL(siInsertionTexte(int, int, QString)), ClientSynergie::Instance(), SLOT(slInsertionTexte(int, int, QString)));
    connect (this, SIGNAL(siEffacementTexte(int, int, int)), ClientSynergie::Instance(), SLOT(slEffacementTexte(int, int, int)));
    connect (this, SIGNAL(siEnvoiTexteChat(QString)), ClientSynergie::Instance()->getChat(), SLOT(slEnvoyer(QString)));
    connect (this, SIGNAL(siMauvaiseSynchro(int)), ClientSynergie::Instance(), SLOT(slMauvaiseSynchro(int)));
    connect (this, SIGNAL(siFermerFichier(int)),ClientSynergie::Instance(),SLOT(slFermerFichier(int)));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::AjouterCollegue(Collegue* collegue)
{
    QListWidgetItem* item = new QListWidgetItem(QIcon(":/Icones/utilisateur.png"), collegue->getNom());
    ui->lstCollegues->addItem(item);
    m_Collegues->insert(collegue, item);
}

void FenetrePrincipale::AjouterFeuille(Feuille *feuille)
{
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, feuille->getNom());
    ui->treeProjet->addTopLevelItem(item);
    m_Feuilles->insert(feuille, item);
}

void FenetrePrincipale::slConnexionCollegues(Collegue *collegue)
{
    AjouterCollegue(collegue);
}

void FenetrePrincipale::slDeconnexionCollegues(Collegue* collegue)
{
    delete m_Collegues->value(collegue);
    m_Collegues->remove(collegue);
}

void FenetrePrincipale::on_treeProjet_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if (item->childCount() == 0)
    {
        Feuille* feuille = m_Feuilles->key(item);

        if (!m_FeuillesOuvertes->contains(feuille))
        {
            ClientSynergie::Instance()->getConnexion()->EnvoyerPaquet(new PaquetOuvrirFeuille(feuille->getID()));
        }
        else
        {
            int index = ui->tabFeuilles->indexOf(m_FeuillesOuvertes->value(feuille));
            ui->tabFeuilles->setCurrentIndex(index);
        }
    }
}

void FenetrePrincipale::on_tabFeuilles_currentChanged(int index)
{
    if (ui->tabFeuilles->widget(index))
    {
        QsciLexer* lexer = ((QsciScintilla*)ui->tabFeuilles->currentWidget())->lexer();
        if (lexer)
        {
            ui->lblLangage->setText(lexer->language());
        }
    }
}

void FenetrePrincipale::on_tabFeuilles_tabCloseRequested(int index)
{
    QsciScintilla* editeur = (QsciScintilla*)ui->tabFeuilles->widget(index);

    emit(siFermerFichier(m_FeuillesOuvertes->key(editeur)->getID()));

    m_FeuillesOuvertes->remove(m_FeuillesOuvertes->key(editeur));
    delete editeur;
}

void FenetrePrincipale::slOuvrirFichier(int id)
{
    Feuille* feuille = ClientSynergie::Instance()->getFeuille(id);
    QString extension = QFileInfo(feuille->getNom()).suffix();

    QsciScintilla* editeur = new QsciScintilla();
    editeur->setMarginLineNumbers(1, true);
    editeur->setMarginWidth(1, 30);

    QsciLexer* lexer = Utils::TrouverLexer(extension);
    if (lexer)
    {
        editeur->setLexer(lexer);
        editeur->lexer()->setFont(QFont("Monospace", 9));
    }
    //editeur->setAutoIndent(true);

    int index = ui->tabFeuilles->addTab(editeur, feuille->getNom());
    ui->tabFeuilles->setCurrentIndex(index);
    m_FeuillesOuvertes->insert(feuille, editeur);

    connect (editeur, SIGNAL(textInserted(int, QString)), this, SLOT(slInsertionTexteEditeur(int, QString)));
    connect (editeur, SIGNAL(textDeleted(int, int)), this, SLOT(slEffacementTexteEditeur(int, int)));
}

void FenetrePrincipale::slNouvelleDonnees(int id, QString contenu)
{
    QsciScintilla* editeur = getEditeur(id);
    editeur->insertAtPosMecha(contenu, editeur->length() - 1); // Changer pour un append ?
}

void FenetrePrincipale::slInsertionTexteEditeur(int position, QString texte)
{
    int id = m_FeuillesOuvertes->key((QsciScintilla*)ui->tabFeuilles->currentWidget())->getID();

    emit (siInsertionTexte(id, position, texte));
}

void FenetrePrincipale::slInsertionTexteServeur(int id, int position, QString texte)
{
    getEditeur(id)->insertAtPosMecha(texte, position);
}

void FenetrePrincipale::slEffacementTexteEditeur(int pos, int longeur)
{
    int id = m_FeuillesOuvertes->key((QsciScintilla*)ui->tabFeuilles->currentWidget())->getID();

    emit (siEffacementTexte(id, pos, longeur));
}

void FenetrePrincipale::slEffacementTexteServeur(int id, int position, int longeur)
{
    QsciScintilla* editeur = getEditeur(id);
    editeur->remove(position, longeur);
}

void FenetrePrincipale::slMessageChat(Collegue* collegue, QString message)
{
    QString ligne = collegue->getNom() + " : " + message;
    ui->txtConversation->append(ligne);
}

void FenetrePrincipale::slAjoutFeuille(Feuille *feuille)
{
    AjouterFeuille(feuille);
}

void FenetrePrincipale::on_txtLigneConv_returnPressed()
{
    QString message = ui->txtLigneConv->text();
    ui->txtConversation->append(ClientSynergie::Instance()->getNom() + " : " + message);
    ui->txtLigneConv->clear();

   emit(siEnvoiTexteChat(message));
}

void FenetrePrincipale::slVerification(int id, int longueur)
{
    if (getEditeur(id))
    {
        if (longueur != getEditeur(id)->length())
        {
            emit(siMauvaiseSynchro(id));
        }
    }
}

void FenetrePrincipale::slNettoyer(int id)
{
    getEditeur(id)->clear();
}

QsciScintilla* FenetrePrincipale::getEditeur(int id)
{
    return getEditeur(ClientSynergie::Instance()->getFeuille(id));
}

QsciScintilla* FenetrePrincipale::getEditeur(Feuille* feuille)
{
    return m_FeuillesOuvertes->value(feuille);
}
