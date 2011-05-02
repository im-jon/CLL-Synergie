#-------------------------------------------------
#
# Project created by QtCreator 2011-04-24T12:03:50
#
#-------------------------------------------------

QT       += core gui network

TARGET = Serveur_Synergie
TEMPLATE = app


SOURCES += main.cpp\
        fenetreprincipale.cpp \
    Console/console.cpp \
    Console/Commandes/basecommande.cpp \
    Console/Commandes/aide.cpp \
    Console/Commandes/vider.cpp \
    serveursynergie.cpp \
    Reseau/client.cpp \
    Console/Commandes/demarrer.cpp \
    Reseau/mangepaquetsserveur.cpp \
    Reseau/Paquets/paquetenvoicollegues.cpp \
    Reseau/Paquets/basepaquetserveur.cpp \
    Console/Commandes/collegues.cpp \
    Reseau/Paquets/paquetlistefichiers.cpp \
    Console/Commandes/fichiers.cpp \
    Reseau/Paquets/paquetconnexioncollegue.cpp \
    Reseau/Paquets/paquetdeconnexioncollegue.cpp \
    Reseau/Paquets/paquetouverturefichier.cpp

HEADERS  += fenetreprincipale.h \
    Console/console.h \
    Console/Commandes/basecommande.h \
    Console/Commandes/aide.h \
    Console/Commandes/vider.h \
    serveursynergie.h \
    Reseau/client.h \
    Console/Commandes/demarrer.h \
    Reseau/mangepaquetsserveur.h \
    Reseau/Paquets/paquetenvoicollegues.h \
    Reseau/Paquets/basepaquetserveur.h \
    Console/Commandes/collegues.h \
    Reseau/Paquets/paquetlistefichiers.h \
    Console/Commandes/fichiers.h \
    Reseau/Paquets/paquetconnexioncollegue.h \
    Reseau/Paquets/paquetdeconnexioncollegue.h \
    Reseau/Paquets/paquetouverturefichier.h

FORMS    += fenetreprincipale.ui
