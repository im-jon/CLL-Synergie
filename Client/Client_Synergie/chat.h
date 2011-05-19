#ifndef CHAT_H
#define CHAT_H

#include <QObject>
#include "collegue.h"

class Chat : public QObject
{
    Q_OBJECT
public:
    explicit Chat(QObject *parent = 0);

    void MessageRecu(Collegue* auteur, QString message);
    void MessageGeneral(QString message);

signals:
    void siMessageRecu(Collegue* auteur, QString message);
    void siMessageGeneral(QString message);

public slots:
    void slEnvoyer(QString message);
};

#endif // CHAT_H
