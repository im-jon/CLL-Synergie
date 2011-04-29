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
    dlgconnexion.cpp

HEADERS  += fenetreprincipale.h \
         ../QScintilla/qscintilla/Qsci/qsciscintilla.h \
    Reseau/connexion.h \
    Reseau/mangepaquetclient.h \
    Reseau/Paquets/basepaquet.h \
    Reseau/Paquets/paquetchangernom.h \
    dlgconnexion.h

FORMS    += fenetreprincipale.ui \
    dlgconnexion.ui

LIBS += -lqscintilla2
