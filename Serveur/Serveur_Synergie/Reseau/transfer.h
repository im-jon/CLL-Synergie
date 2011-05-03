#ifndef TRANSFER_H
#define TRANSFER_H

#include <QFile>
#include <QTextStream>

class Transfer
{
public:
    Transfer(int id);
    QString LireBloc();
    bool estFini();
    int getFeuilleID();

private:
    QTextStream* m_Stream;
    QFile* m_Fichier;
    bool m_Fini;
    int m_FeuilleID;
};

#endif // TRANSFER_H
