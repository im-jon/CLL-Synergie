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
    Reseau/connexion.cpp

HEADERS  += fenetreprincipale.h \
         ../QScintilla/qscintilla/Qsci/qsciscintilla.h \
    Reseau/connexion.h

FORMS    += fenetreprincipale.ui

LIBS += -L../QScintilla/Librairie -lqscintilla2
