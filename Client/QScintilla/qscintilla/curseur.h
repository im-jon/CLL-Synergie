#ifndef CURSEUR_H
#define CURSEUR_H

#include <QColor>
#include "../include/Platform.h"

class Curseur
{
public:
    Curseur(int id, int position, QColor couleur);

    int getID();
    int getPosition();
    int getLigne();
    int getIndex();
    ColourAllocated getCouleur();

    void setPosition(int position);
    void setLigne(int ligne);
    void setIndex(int index);

private:    
    int m_ID;
    int m_Position;
    int m_Ligne;
    int m_Index;
    ColourAllocated m_Couleur;

};

#endif // CURSEUR_H
