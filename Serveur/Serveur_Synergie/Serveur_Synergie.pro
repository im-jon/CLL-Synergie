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
    Reseau/client.cpp \
    Console/Commandes/demarrer.cpp \
    Reseau/Paquets/paquetenvoicollegues.cpp \
    Console/Commandes/collegues.cpp \
    Reseau/Paquets/paquetlistefichiers.cpp \
    Console/Commandes/fichiers.cpp \
    Reseau/Paquets/paquetconnexioncollegue.cpp \
    Reseau/Paquets/paquetdeconnexioncollegue.cpp \
    Reseau/Paquets/paquetouverturefichier.cpp \
    Reseau/Paquets/paquetdonnees.cpp \
    fichier.cpp \
    Reseau/Paquets/paquetinsertiontexte.cpp \
    Reseau/Paquets/paqueteffacementtexte.cpp \
    projet.cpp \
    Reseau/transfer.cpp \
    clients.cpp \
    serveur.cpp \
    Reseau/Paquets/basepaquet.cpp \
    Reseau/depaqueteur.cpp \
    Reseau/Paquets/paquetmessagechat.cpp \
    chat.cpp \
    verificateur.cpp \
    Reseau/Paquets/paquetverification.cpp \
    Reseau/Paquets/paquetnettoyerfichier.cpp

HEADERS  += fenetreprincipale.h \
    Console/console.h \
    Console/Commandes/basecommande.h \
    Console/Commandes/aide.h \
    Console/Commandes/vider.h \
    Reseau/client.h \
    Console/Commandes/demarrer.h \
    Reseau/Paquets/paquetenvoicollegues.h \
    Console/Commandes/collegues.h \
    Reseau/Paquets/paquetlistefichiers.h \
    Console/Commandes/fichiers.h \
    Reseau/Paquets/paquetconnexioncollegue.h \
    Reseau/Paquets/paquetdeconnexioncollegue.h \
    Reseau/Paquets/paquetouverturefichier.h \
    Reseau/Paquets/paquetdonnees.h \
    fichier.h \
    Reseau/Paquets/paquetinsertiontexte.h \
    Reseau/Paquets/paqueteffacementtexte.h \
    projet.h \
    Reseau/transfer.h \
    clients.h \
    serveur.h \
    Reseau/Paquets/basepaquet.h \
    Reseau/depaqueteur.h \
    Reseau/Paquets/paquetmessagechat.h \
    chat.h \
    verificateur.h \
    Reseau/Paquets/paquetverification.h \
    Reseau/Paquets/paquetnettoyerfichier.h

FORMS    += fenetreprincipale.ui
