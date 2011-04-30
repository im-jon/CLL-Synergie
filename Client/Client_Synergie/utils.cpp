#include "utils.h"
#include <QtCore>
#include <QMapIterator>
#include <../QScintilla/qscintilla/Qsci/qscilexercpp.h>
#include <../QScintilla/qscintilla/Qsci/qscilexercsharp.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerjava.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerjavascript.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerpython.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerruby.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerperl.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerhtml.h>
#include <../QScintilla/qscintilla/Qsci/qscilexersql.h>
#include <../QScintilla/qscintilla/Qsci/qscilexercss.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerbash.h>
#include <../QScintilla/qscintilla/Qsci/qscilexerxml.h>

QMap<int, QStringList>* Utils::m_Extensions = 0;

void Utils::InitialiserExtensions()
{
    m_Extensions = new QMap<int, QStringList>();

    m_Extensions->insert(0, QStringList() << "cpp" << "h" << "cxx" << "hxx" << "c++"); // C++
    m_Extensions->insert(1, QStringList() << "cs");
    m_Extensions->insert(2, QStringList() << "java" << "class" << "jar");
    m_Extensions->insert(3, QStringList() << "js");
    m_Extensions->insert(4, QStringList() << "py" << "pyw" << "pyc" << "pyo" << "pyd");
    m_Extensions->insert(5, QStringList() << "rb" << "rbw");
    m_Extensions->insert(6, QStringList() << "pl" << "pm");
    m_Extensions->insert(7, QStringList() << "html" << "htm");
    m_Extensions->insert(8, QStringList() << "sql");
    m_Extensions->insert(9, QStringList() << "css");
    m_Extensions->insert(10, QStringList() << "sh");
    m_Extensions->insert(11, QStringList() << "xml");
}

QsciLexer* Utils::TrouverLexer(QString extension)
{
    if (!m_Extensions) {
        InitialiserExtensions();
    }

    QMapIterator<int, QStringList> iterateur(*m_Extensions);
    bool trouver = false;
    while (iterateur.hasNext() && !trouver) {
        iterateur.next();
        if (iterateur.value().contains(extension)) {
            trouver = true;
        }
    }

    if (!trouver) {
        return 0;
    }

    switch (iterateur.key()) {
        case 0:
            return new QsciLexerCPP();
        case 1:
            return new QsciLexerCSharp();
        case 2:
            return new QsciLexerJava();
        case 3:
            return new QsciLexerJavaScript();
        case 4:
            return new QsciLexerPython();
        case 5:
            return new QsciLexerRuby();
        case 6:
            return new QsciLexerPerl();
        case 7:
            return new QsciLexerHTML();
        case 8:
            return new QsciLexerSQL();
        case 9:
            return new QsciLexerCSS();
        case 10:
            return new QsciLexerBash();
        case 11:
            return new QsciLexerXML();
        default:
            return 0;
    }

}
