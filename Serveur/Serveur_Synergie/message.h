#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include "client.h"

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(Client* auteur, QString contenu, QObject *parent = 0);
    void Archiver();
    Client* getAuteur();
    QString getContenu();

private:
    Client* m_Auteur;
    QString m_Contenu;

signals:

public slots:

};

#endif // MESSAGE_H
