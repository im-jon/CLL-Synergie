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
#include <../QScintilla/qscintilla/curseur.h>

FenetrePrincipale::FenetrePrincipale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FenetrePrincipale)
{
    ui->setupUi(this);
    this->showMaximized();

    m_Collegues = new QMap<Collegue*, QListWidgetItem*>;
    m_Feuilles = new QMap<Feuille*, QTreeWidgetItem*>;
    m_FeuillesOuvertes = new QMap<Feuille*, QsciScintilla*>;

    connect (ClientSynergie::Instance(), SIGNAL(siConnexionCollegue(Collegue*)), this, SLOT(slConnexionCollegues(Collegue*)));
    connect (ClientSynergie::Instance(), SIGNAL(siDeconnexionCollegue(Collegue*)), this, SLOT(slDeconnexionCollegues(Collegue*)));
    connect (ClientSynergie::Instance(), SIGNAL(siAjoutFeuille(Feuille*)), this, SLOT(slAjoutFeuille(Feuille*)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siOuvrirFichier(int)), this, SLOT(slOuvrirFeuille(int)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siDonnees(int, QString)), this, SLOT(slNouvelleDonnees(int, QString)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siInsertionTexte(int, int, int, QString)), this, SLOT(slInsertionTexteServeur(int, int, int, QString)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siEffacementTexte(int, int, int, int)), this, SLOT(slEffacementTexteServeur(int, int, int, int)));
    connect (ClientSynergie::Instance()->getChat(), SIGNAL(siMessageRecu(Collegue*,QString)), this, SLOT(slMessageChat(Collegue*, QString)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siVerification(int, int)), this, SLOT(slVerification(int, int)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siNettoyer(int)), this,SLOT(slNettoyerFeuille(int)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siCollegueOuvertureFeuille(Collegue*, int, int)), this, SLOT(slCollegueOuvertureFeuille(Collegue*, int, int)));
    connect (ClientSynergie::Instance()->getDepaqueteur(), SIGNAL(siCollegueFermetureFeuille(int, int)), this, SLOT(slCollegueFermetureFeuille(int, int)));

    connect (this, SIGNAL(siInsertionTexte(int, int, QString)), ClientSynergie::Instance(), SLOT(slInsertionTexte(int, int, QString)));
    connect (this, SIGNAL(siEffacementTexte(int, int, int)), ClientSynergie::Instance(), SLOT(slEffacementTexte(int, int, int)));
    connect (this, SIGNAL(siEnvoiTexteChat(QString)), ClientSynergie::Instance()->getChat(), SLOT(slEnvoyer(QString)));
    connect (this, SIGNAL(siVerification(int,bool)), ClientSynergie::Instance(), SLOT(slVerification(int,bool)));
    connect (this, SIGNAL(siFermerFeuille(int)),ClientSynergie::Instance(),SLOT(slFermerFichier(int)));
}

FenetrePrincipale::~FenetrePrincipale()
{
    delete ui;
}

void FenetrePrincipale::AjouterCollegue(Collegue* collegue)
{
    QListWidgetItem* item = new QListWidgetItem(QIcon(":/Icones/utilisateur.png"), collegue->getNom());
    item->setTextColor(collegue->getCouleur());
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

    emit siFermerFeuille(m_FeuillesOuvertes->key(editeur)->getID());

    m_FeuillesOuvertes->remove(m_FeuillesOuvertes->key(editeur));
    delete editeur;
}

void FenetrePrincipale::slOuvrirFeuille(int idFeuille)
{
    Feuille* feuille = ClientSynergie::Instance()->getFeuille(idFeuille);
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
    editeur->insertAtPosMecha(contenu, editeur->text().length()); // Changer pour un append ?
}

void FenetrePrincipale::slInsertionTexteEditeur(int position, QString texte)
{
    QsciScintilla* editeur = (QsciScintilla*)sender();

    QMapIterator<int, Curseur*> iterateur(*editeur->getCurseurs());
    while (iterateur.hasNext())
    {
        iterateur.next();
        if (iterateur.value()->getPosition() > position)
        {
            editeur->deplacerCurseur(iterateur.value()->getID(), texte.length());
        }
    }

    emit siInsertionTexte(m_FeuillesOuvertes->key(editeur)->getID(), position, texte);
}

void FenetrePrincipale::slInsertionTexteServeur(int idCollegue, int idFeuille, int position, QString texte)
{
    QsciScintilla* editeur = getEditeur(idFeuille);
    editeur->insertAtPosMecha(texte, position);

    editeur->setCurseurPosition(idCollegue, position + texte.length());

    QMapIterator<int, Curseur*> iterateur(*editeur->getCurseurs());
    while (iterateur.hasNext())
    {
        iterateur.next();
        if (iterateur.value()->getID() != idCollegue)
        {
            if (iterateur.value()->getPosition() > position)
            {
                editeur->deplacerCurseur(iterateur.value()->getID(), texte.length());
            }
        }
    }
}

void FenetrePrincipale::slEffacementTexteEditeur(int position, int longeur)
{
    QsciScintilla* editeur = (QsciScintilla*)sender();

    QMapIterator<int, Curseur*> iterateur(*editeur->getCurseurs());
    while (iterateur.hasNext())
    {
        iterateur.next();
        if (iterateur.value()->getPosition() > position)
        {
            editeur->deplacerCurseur(iterateur.value()->getID(), 0 - longeur);
        }
    }

    emit siEffacementTexte(m_FeuillesOuvertes->key(editeur)->getID(), position, longeur);
}

void FenetrePrincipale::slEffacementTexteServeur(int idAuteur, int idFeuille, int position, int longeur)
{
    QsciScintilla* editeur = getEditeur(idFeuille);
    editeur->remove(position, longeur);

    editeur->setCurseurPosition(idAuteur, position);

    QMapIterator<int, Curseur*> iterateur(*editeur->getCurseurs());
    while (iterateur.hasNext())
    {
        iterateur.next();
        if (iterateur.value()->getID() != idAuteur)
        {
            if (iterateur.value()->getPosition() > position)
            {
                editeur->deplacerCurseur(iterateur.value()->getID(), 0 - longeur);
            }
        }
    }
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
    if (!message.isEmpty())
    {
        ui->txtConversation->append(ClientSynergie::Instance()->getNom() + " : " + message);
        ui->txtLigneConv->clear();

       emit siEnvoiTexteChat(message);
    }
}

void FenetrePrincipale::slVerification(int idFeuille, int longueur)
{
    if (getEditeur(idFeuille))
    {
        bool reponse = (longueur == getEditeur(idFeuille)->length());
        emit siVerification(idFeuille, reponse);
    }
}

void FenetrePrincipale::slNettoyerFeuille(int idFeuille)
{
    getEditeur(idFeuille)->clear();
}

QsciScintilla* FenetrePrincipale::getEditeur(int idFeuille)
{
    return getEditeur(ClientSynergie::Instance()->getFeuille(idFeuille));
}

QsciScintilla* FenetrePrincipale::getEditeur(Feuille* feuille)
{
    return m_FeuillesOuvertes->value(feuille);
}

void FenetrePrincipale::slCollegueOuvertureFeuille(Collegue* collegue, int idFeuille, int position)
{
    QsciScintilla* editeur = getEditeur(idFeuille);
    editeur->ajouterCurseur(
                new Curseur(
                    collegue->getID(),
                    position,
                    collegue->getCouleur()));
}

void FenetrePrincipale::slCollegueFermetureFeuille(int idCollegue, int idFeuille)
{
    QsciScintilla* editeur = getEditeur(idFeuille);
    editeur->enleverCurseur(idCollegue);
}
