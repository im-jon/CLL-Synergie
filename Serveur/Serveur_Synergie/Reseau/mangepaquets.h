#ifndef MANGEPAQUETS_H
#define MANGEPAQUETS_H

#include <QObject>
#include "client.h"

class MangePaquets : public QObject
{
    Q_OBJECT
public:
    explicit MangePaquets(QObject* parent = 0);
    void Interpreter(Client* client, QDataStream& stream);

private:
    void Reception_ChangerNom(Client* client, QDataStream& stream);
    void Reception_OuvrirFichier(Client* client, QDataStream& stream);
    void Reception_DonneesRecues(Client* client, QDataStream& stream);
    void Reception_InsertionTexte(Client* client, QDataStream& stream);
    void Reception_EffacementTexte(Client* client, QDataStream& stream);

signals:

public slots:

};

#endif // MANGEPAQUETSSERVEUR_H
