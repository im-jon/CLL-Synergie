#ifndef MANGEPAQUETCLIENT_H
#define MANGEPAQUETCLIENT_H

#include <QObject>
#include <QMap>

class MangePaquetClient : public QObject
{
    Q_OBJECT
public:
    explicit MangePaquetClient(QObject *parent = 0);
    void Interpreter(QDataStream*);

private:
    void Reception_ListeCollegues(QDataStream* stream);
    void Reception_ListeDesFichiers(QDataStream* stream);

signals:
    void siNouvelleListeCollegues(QStringList* noms);
    void NouvelleListeFichiers(QStringList* noms);

public slots:
};

#endif // MANGEPAQUETCLIENT_H
