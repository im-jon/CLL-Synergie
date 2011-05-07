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

    connect (ClientSynergie::getInstance(), SIGNAL(siConnexionCollegue(Collegue*)), this, SLOT(slConnexionCollegues(Collegue*)));
    connect (ClientSynergie::getInstance(), SIGNAL(siDeconnexionCollegue(Collegue*)), this, SLOT(slDeconnexionCollegues(Collegue*)));
    connect (ClientSynergie::getInstance(), SIGNAL(siAjoutFeuille(Feuille*)), this, SLOT(slAjoutFeuille(Feuille*)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siOuvrirFichier(int)), this, SLOT(slOuvrirFichier(int)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siDonnees(int, QString)), this, SLOT(slNouvelleDonnees(int, QString)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siInsertionTexte(int, int, QString)), this, SLOT(slInsertionTexteServeur(int, int, QString)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siEffacementTexte(int, int, int)), this, SLOT(slEffacementTexteServeur(int, int, int)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siTexteChat(Collegue*, QString)), this, SLOT(slTexteChat(Collegue*, QString)));

    connect (this, SIGNAL(siInsertionTexte(int, int, QString)), ClientSynergie::getInstance(), SLOT(slInsertionTexte(int, int, QString)));
    connect (this, SIGNAL(siEffacementTexte(int, int, int)), ClientSynergie::getInstance(), SLOT(slEffacementTexte(int, int, int)));
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
            ClientSynergie::getInstance()->getConnexion()->EnvoyerPaquet(new PaquetOuvrirFeuille(feuille->getID()));
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

        // Envoyer le paquet pour changer la feuille active.
    }
}

void FenetrePrincipale::on_tabFeuilles_tabCloseRequested(int index)
{
    QsciScintilla* editeur = (QsciScintilla*)ui->tabFeuilles->widget(index);
    m_FeuillesOuvertes->remove(m_FeuillesOuvertes->key(editeur));
    delete editeur;
}

void FenetrePrincipale::slOuvrirFichier(int id)
{
    Feuille* feuille = ClientSynergie::getInstance()->getFeuille(id);
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
    editeur->setAutoIndent(true);

    int index = ui->tabFeuilles->addTab(editeur, feuille->getNom());
    ui->tabFeuilles->setCurrentIndex(index);
    m_FeuillesOuvertes->insert(feuille, editeur);

    connect (editeur, SIGNAL(textInserted(int, QString)), this, SLOT(slInsertionTexteEditeur(int, QString)));
    connect (editeur, SIGNAL(textDeleted(int, int)), this, SLOT(slEffacementTexteEditeur(int, int)));
}

void FenetrePrincipale::slNouvelleDonnees(int id, QString contenu)
{
    QsciScintilla* editeur = getEditeur(id);
    editeur->insertAtPosMecha(contenu, editeur->length() - 1);
}

void FenetrePrincipale::slInsertionTexteEditeur(int position, QString texte)
{
    int id = m_FeuillesOuvertes->key((QsciScintilla*)ui->tabFeuilles->currentWidget())->getID();

    emit (siInsertionTexte(id, position, texte));
}

QsciScintilla* FenetrePrincipale::getEditeur(int id)
{
    return getEditeur(ClientSynergie::getInstance()->getFeuille(id));
}

QsciScintilla* FenetrePrincipale::getEditeur(Feuille* feuille)
{
    return m_FeuillesOuvertes->value(feuille);
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

    int ligneDebut;
    int indexDebut;
    editeur->lineIndexFromPosition(position, &ligneDebut, &indexDebut);

    int ligneFin;
    int indexFin;
    editeur->lineIndexFromPosition(position + longeur, &ligneFin, &indexFin);

    editeur->setSelection(ligneDebut, indexDebut, ligneFin, indexFin);
    editeur->removeSelectedTextMecha();
}

void FenetrePrincipale::slTexteChat(Collegue* collegue, QString message)
{
    QString ligne = "\n" + collegue->getNom() + " : " + message;
    ui->txtConversation->append(ligne);
}

void FenetrePrincipale::slAjoutFeuille(Feuille *feuille)
{
    AjouterFeuille(feuille);
}
