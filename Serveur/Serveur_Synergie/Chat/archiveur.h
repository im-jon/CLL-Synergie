#ifndef ARCHIVEUR_H
#define ARCHIVEUR_H

#include <QObject>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "message.h"

// L'archiveur enregistre tous les messages envoyés sur le chat du serveur dans
// un fichier nommé selon la date actuelle pour faciliter l'organisation des
// archives.

class Archiveur : public QObject
{
    Q_OBJECT
public:
    explicit Archiveur(QObject *parent = 0);

    void Demarrer();
    void Arreter();
    void Archiver(Message* message);
    void Archiver(QList<Message*>* messages);

private:
    bool m_Actif;
    QString m_NomFichier;
    QDir* m_Repertoire;
    QFile* m_FichierActuel;
    QTextStream* m_Stream;

signals:

public slots:

};

#endif // ARCHIVEUR_H
