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

QMap<QsciLexer*, QStringList>* Utils::m_Extensions = 0;

QsciLexer* Utils::TrouverLexer(QString extension)
{
    if (!m_Extensions) {
        InitialiserExtensions();
    }

    extension = extension.toLower();
    QMapIterator<QsciLexer*, QStringList> iterateur(*m_Extensions);
    bool trouver = false;
    while (iterateur.hasNext() && !trouver) {
        iterateur.next();
        if (iterateur.value().contains(extension)) {
            trouver = true;
        }
    }

    if (trouver) {
        return iterateur.key();
    }
    return 0;
}

void Utils::InitialiserExtensions()
{
    m_Extensions = new QMap<QsciLexer*, QStringList>();

    m_Extensions->insert(new QsciLexerCPP, QStringList() << "cpp" << "h" << "cxx" << "hxx" << "c++"); // C++
    m_Extensions->insert(new QsciLexerCSharp, QStringList() << "cs");
    m_Extensions->insert(new QsciLexerJava, QStringList() << "java" << "class" << "jar");
    m_Extensions->insert(new QsciLexerJavaScript, QStringList() << "js");
    m_Extensions->insert(new QsciLexerPython, QStringList() << "py" << "pyw" << "pyc" << "pyo" << "pyd");
    m_Extensions->insert(new QsciLexerRuby, QStringList() << "rb" << "rbw");
    m_Extensions->insert(new QsciLexerPerl, QStringList() << "pl" << "pm");
    m_Extensions->insert(new QsciLexerHTML, QStringList() << "html" << "htm");
    m_Extensions->insert(new QsciLexerSQL, QStringList() << "sql");
    m_Extensions->insert(new QsciLexerCSS, QStringList() << "css");
    m_Extensions->insert(new QsciLexerBash, QStringList() << "sh");
    m_Extensions->insert(new QsciLexerXML, QStringList() << "xml");
}

