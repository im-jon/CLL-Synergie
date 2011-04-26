#ifndef AIDE_H
#define AIDE_H

#include "basecommande.h"
#include <QStringList>

class Aide : public BaseCommande
{
    Q_OBJECT
public:
    explicit Aide();

protected:
    QString Executer(const QStringList &arguments);

signals:

public slots:

};

#endif // AIDE_H
