#-------------------------------------------------
#
# Project created by QtCreator 2011-04-24T11:23:41
#
#-------------------------------------------------

QT       += core gui network

TARGET = Client_Synergie
TEMPLATE = app


SOURCES += main.cpp\
        fenetreprincipale.cpp \
    Reseau/connexion.cpp \
    Reseau/Paquets/basepaquet.cpp \
    dlgconnexion.cpp \
    utils.cpp \
    Reseau/Paquets/paquetreceptiondonnees.cpp \
    clientsynergie.cpp \
    Reseau/Paquets/paquetinsertiontexte.cpp \
    Reseau/Paquets/paqueteffacementtexte.cpp \
    collegue.cpp \
    Reseau/Paquets/paquetenvoichat.cpp \
    feuille.cpp \
    Reseau/Paquets/paquetouvrirfeuille.cpp \
    Reseau/depaqueteur.cpp \
    Reseau/Paquets/paquetfermerfichier.cpp \
    Reseau/Paquets/paquetmauvaisesynchro.cpp \
    chat.cpp \
    Reseau/Paquets/paquetauthentification.cpp \
    Reseau/Paquets/paquetlignechangee.cpp

HEADERS  += fenetreprincipale.h \
    Reseau/connexion.h \
    Reseau/Paquets/basepaquet.h \
    dlgconnexion.h \
    utils.h \
    Reseau/Paquets/paquetreceptiondonnees.h \
    clientsynergie.h \
    Reseau/Paquets/paquetinsertiontexte.h \
    Reseau/Paquets/paqueteffacementtexte.h \
    collegue.h \
    Reseau/Paquets/paquetenvoichat.h \
    feuille.h \
    Reseau/Paquets/paquetouvrirfeuille.h \
    Reseau/depaqueteur.h \
    Reseau/Paquets/paquetfermerfichier.h \
    Reseau/Paquets/paquetmauvaisesynchro.h \
    chat.h \
    Reseau/Paquets/paquetauthentification.h \
    Reseau/Paquets/paquetlignechangee.h

FORMS    += fenetreprincipale.ui \
    dlgconnexion.ui

LIBS += "../QScintilla/Librairie/libqscintilla2.a"

RESOURCES += \
    Ressources.qrc
