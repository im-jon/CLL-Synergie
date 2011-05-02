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
    Reseau/mangepaquetclient.cpp \
    Reseau/Paquets/basepaquet.cpp \
    Reseau/Paquets/paquetchangernom.cpp \
    dlgconnexion.cpp \
    utils.cpp \
    Reseau/Paquets/paquetouvrirfichier.cpp

HEADERS  += fenetreprincipale.h \
    Reseau/connexion.h \
    Reseau/mangepaquetclient.h \
    Reseau/Paquets/basepaquet.h \
    Reseau/Paquets/paquetchangernom.h \
    dlgconnexion.h \
    utils.h \
    Reseau/Paquets/paquetouvrirfichier.h

FORMS    += fenetreprincipale.ui \
    dlgconnexion.ui

LIBS += "../QScintilla/Librairie/libqscintilla2.a"

RESOURCES += \
    Ressources.qrc
