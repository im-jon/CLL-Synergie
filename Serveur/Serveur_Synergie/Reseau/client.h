#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QTcpSocket* socket);

private:
    QTcpSocket* m_Socket;

signals:

public slots:
    void slPretALire();
    void slOnDeconnection();
};

#endif // CLIENT_H
