#include "basecommande.h"
#include "Console/console.h"
#include "aide.h"
#include "vider.h"

QList<BaseCommande*>* BaseCommande::ListeCommandes = new QList<BaseCommande*>;

void BaseCommande::InitialiserListe()
{
    ListeCommandes->append(new Aide());
    ListeCommandes->append(new Vider());

}

BaseCommande::BaseCommande()
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

QString BaseCommande::Executer(const QStringList &arguments)
{
}
