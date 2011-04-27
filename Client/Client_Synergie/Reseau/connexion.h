#ifndef CONNEXION_H
#define CONNEXION_H

#include <QObject>
#include <QTcpSocket>

class Connexion : public QObject
{
    Q_OBJECT
public:   
    bool Connecter(QString, int);
    static Connexion* getInstance();

private:
    explicit Connexion(QObject *parent = 0);
    static Connexion* m_Instance;
    QTcpSocket* m_Socket;

signals:

public slots:

};

#endif // CONNEXION_H
