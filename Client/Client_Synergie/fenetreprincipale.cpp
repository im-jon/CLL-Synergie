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
#include <QList>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);

    m_FeuillesOuvertes = new QMap<int, QsciScintilla*>;
    m_Collegues = new QMap<Collegue*, QListWidgetItem*>;

    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siNouvelleListeFichiers(QStringList*)), this, SLOT(slMiseAJourListeFichiers(QStringList*)));
    connect (ClientSynergie::getInstance(), SIGNAL(siConnexionCollegue(Collegue*)), this, SLOT(slConnexionCollegues(Collegue*)));
    connect (ClientSynergie::getInstance(), SIGNAL(siDeconnexionCollegue(Collegue*)), this, SLOT(slDeconnexionCollegues(Collegue*)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siOuvrirFichier(int)), this, SLOT(slOuvrirFichier(int)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siNouvelleDonnees(int, QString)), this, SLOT(slNouvelleDonnees(int, QString)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siInsertionTexteServeur(int, int, QString)), this, SLOT(slNouveauTexte(int, int, QString)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siEffacementTexte(int, int, int)), this, SLOT(slEffacementTexteServeur(int, int, int)));
    connect (ClientSynergie::getInstance()->getMangePaquets(), SIGNAL(siNouveauTexteChat(Collegue*, QString)), this, SLOT(slNouveauTexteChat(Collegue*, QString)));

    connect (this, SIGNAL(siInsertionTexte(int, int, QString)), ClientSynergie::getInstance(), SLOT(slOnInsertionTexte(int, int, QString)));
    connect (this, SIGNAL(siEffacementTexte(int, int, int)), ClientSynergie::getInstance(), SLOT(slEffacementTexte(int, int, int)));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::AjouterCollegueListe(Collegue* collegue)
{
    QListWidgetItem* item = new QListWidgetItem(QIcon(":/Icones/utilisateur.png"), collegue->getNom());
    ui->lstCollegues->addItem(item);
    m_Collegues->insert(collegue, item);
}

void FenetrePrincipale::slConnexionCollegues(Collegue *collegue)
{
    AjouterCollegueListe(collegue);
}

void FenetrePrincipale::slDeconnexionCollegues(Collegue* collegue)
{
    delete m_Collegues->value(collegue);
    m_Collegues->remove(collegue);
}

void FenetrePrincipale::slMiseAJourListeFichiers(QStringList* fichiers)
{
    ui->treeProjet->clear();

    for (int i = 0; i < fichiers->length(); i++)
    {
        QStringList parties = fichiers->at(i).split('/');
        QString partie;
        QTreeWidgetItem* parent;

        foreach (partie, parties)
        {
            QList<QTreeWidgetItem*> resultats = ui->treeProjet->findItems(partie, Qt::MatchExactly);

            if (resultats.count() > 0)
            {
                parent = resultats.first();
            }
        }

        QTreeWidgetItem* item = new QTreeWidgetItem();
        item->setText(0, parties.last());

        if (parent)
        {
            parent->addChild(item);
        }
        else
        {
            ui->treeProjet->addTopLevelItem(item);
        }
        parent = item;
    }
}

void FenetrePrincipale::on_treeProjet_itemDoubleClicked(QTreeWidgetItem* item, int column)
{
    if (item->childCount() == 0)
    {
        int id = ClientSynergie::getInstance()->TrouverFichierParNom(item->text(column));
        if (!m_FeuillesOuvertes->contains(id))
        {
            ClientSynergie::getInstance()->getConnexion()->EnvoyerPaquet(new PaquetOuvrirFichier(id));
        }
        else
        {
            int index = ui->tabFeuilles->indexOf(m_FeuillesOuvertes->value(id));
            ui->tabFeuilles->setCurrentIndex(index);
        }
    }
}

void FenetrePrincipale::on_tabFeuilles_currentChanged(int index)
{
    QsciLexer* lexer = ((QsciScintilla*)ui->tabFeuilles->currentWidget())->lexer();
    if (lexer)
    {
        ui->lblLangage->setText(lexer->language());
    }

    // Envoyer le paquet pour changer la feuille active.
}

void FenetrePrincipale::on_tabFeuilles_tabCloseRequested(int index)
{
    if (ui->tabFeuilles->count() > 1)
    {
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
    if (lexer)
    {
        editeur->setLexer(lexer);
        editeur->lexer()->setFont(QFont("Monospace", 9));
    }
    editeur->setAutoIndent(true);

    int index = ui->tabFeuilles->addTab(editeur, fichier);
    ui->tabFeuilles->setCurrentIndex(index);
    m_FeuillesOuvertes->insert(id, editeur);
    connect (editeur,SIGNAL(textInserted(int, QString)),this,SLOT(slInsertionTexteEditeur(int, QString)));
    connect (editeur, SIGNAL(textDeleted(int, int)), this, SLOT(slEffacementTexteEditeur(int, int)));
}

void FenetrePrincipale::slNouvelleDonnees(int id, QString contenu)
{
    QsciScintilla* editeur = ChercherEditeurParID(id);
    editeur->insertAtPosMecha(contenu, editeur->length() - 1);
}

void FenetrePrincipale::slInsertionTexteEditeur(int position, QString texte)
{
    int id = m_FeuillesOuvertes->key((QsciScintilla*)ui->tabFeuilles->currentWidget());

    emit (siInsertionTexte(id, position, texte));
}

QsciScintilla* FenetrePrincipale::ChercherEditeurParID(int id)
{
    return m_FeuillesOuvertes->value(id);
}

void FenetrePrincipale::slInsertionTexteServeur(int id, int position, QString texte)
{
    ChercherEditeurParID(id)->insertAtPosMecha(texte, position);
}

void FenetrePrincipale::slEffacementTexteEditeur(int pos, int longeur)
{
    int id = m_FeuillesOuvertes->key((QsciScintilla*)ui->tabFeuilles->currentWidget());

    emit (siEffacementTexte(id, pos, longeur));
}

void FenetrePrincipale::slEffacementTexteServeur(int id, int position, int longeur)
{
    QsciScintilla* editeur = ChercherEditeurParID(id);

    int ligneDebut;
    int indexDebut;
    editeur->lineIndexFromPosition(position, &ligneDebut, &indexDebut);

    int ligneFin;
    int indexFin;
    editeur->lineIndexFromPosition(position + longeur, &ligneFin, &indexFin);

    editeur->setSelection(ligneDebut, indexDebut, ligneFin, indexFin);
    editeur->removeSelectedTextMecha();
}

void FenetrePrincipale::slNouveauTexteChat(Collegue* collegue, QString message)
{
    QString ligne = "\n" + collegue->getNom() + " : " + message;
    ui->txtConversation->append(ligne);
}
