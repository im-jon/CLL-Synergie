#include "console.h"
#include <QStringList>
#include <QDebug>
#include "argument.h"

Console* Console::m_Instance = 0;

Console* Console::Instance()
{
    static QMutex mutex;
    if (!m_Instance)
    {
        mutex.lock();
        m_Instance = new Console;
        mutex.unlock();
    }
    return m_Instance;
}

Console::Console(QObject *parent) :
    QObject(parent)
{
    Initialiser();
}

void Console::Initialiser()
{
    InitialiserListeCommandes();
}

void Console::InitialiserListeCommandes()
{
    BaseCommande::InitialiserListe();

    m_Commandes = new QMap<QString, BaseCommande*>;

    BaseCommande* commande;
    for (int i = 0; i < BaseCommande::ListeCommandes->length(); i++)
    {
        commande = BaseCommande::ListeCommandes->at(i);
        QStringList motscle = commande->getMotsCle();

        for (int j = 0; j < motscle.length(); j++)
        {
            m_Commandes->insert(motscle.at(j), commande);
        }
    }
}

void Console::Ecrire(QString ligne)
{
    QString reponse;
    QString nomCommande;
    BaseCommande* commande;
    QRegExp regex;
    QStringList parties;
    Arguments* arguments = new Arguments();

    nomCommande = ligne.section(' ', 0, 0);
    ligne.remove(0, nomCommande.length());

    regex = QRegExp(" -(\\S*) ?(\".*\"|\\S*\\b?)(.*)");
    do
    {
        regex.indexIn(ligne);
        parties = regex.capturedTexts();
        if (!parties.at(0).isEmpty())
        {
            arguments->Ajouter(new Argument(parties.at(1), parties.at(2)));
        }
        ligne = parties.at(3);
    }
    while (!ligne.isEmpty());

    commande = m_Commandes->value(nomCommande);
    if (commande)
    {
        if (commande->getArgsMin() <= arguments->count())
        {
            reponse = commande->Executer(arguments);
        }
        else
        {
            reponse = nomCommande + " : Pas assez d'arguments";
        }
    } else
    {
        reponse = nomCommande + " : Commande inconnue";
    }
    Imprimer(reponse);
}

void Console::Imprimer(QString ligne)
{
    emit (siSortie(QString::fromUtf8(ligne.toAscii())));
}

void Console::Vider()
{
    emit (siVider());
}
