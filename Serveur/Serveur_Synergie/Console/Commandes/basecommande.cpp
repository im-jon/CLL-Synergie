#include "basecommande.h"
#include "Console/console.h"
#include "aide.h"
#include "vider.h"
#include "collegues.h"
#include "demarrer.h"

QList<BaseCommande*>* BaseCommande::ListeCommandes = new QList<BaseCommande*>;

void BaseCommande::InitialiserListe()
{
    ListeCommandes->append(new Aide());
    ListeCommandes->append(new Vider());
    ListeCommandes->append(new Collegues());
    ListeCommandes->append(new Demarrer());
}

BaseCommande::BaseCommande()
{
}

QString BaseCommande::Executer(const QStringList &arguments)
{
}

const QStringList& BaseCommande::getMotsCle()
{
    return m_MotsCle;
}

int BaseCommande::getArgsMin()
{
    return m_ArgsMin;
}

QString BaseCommande::getDescription()
{
    return m_Description;
}
