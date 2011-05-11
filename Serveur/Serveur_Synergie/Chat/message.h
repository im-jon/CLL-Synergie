#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDateTime>
#include "client.h"

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(Client* auteur, QString contenu, QObject *parent = 0);
    Client* getAuteur();
    QString getContenu();
    QDateTime getDate();

private:
    Client* m_Auteur;
    QString m_Contenu;
    QDateTime m_Date;

signals:

public slots:

};

#endif // MESSAGE_H
