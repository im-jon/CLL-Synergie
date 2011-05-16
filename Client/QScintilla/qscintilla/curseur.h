#ifndef CURSEUR_H
#define CURSEUR_H

#include <QColor>

class Curseur
{
public:
    Curseur(int id, int ligne, QColor* couleur);
    int getID();
    int getLigne();
    QColor* getCouleur();
    void setLigne(int ligne);

private:
    int m_ID;
    int m_Ligne;
    QColor* m_Couleur;

};

#endif // CURSEUR_H
