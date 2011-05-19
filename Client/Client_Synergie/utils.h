#ifndef UTILS_H
#define UTILS_H

#include <../QScintilla/qscintilla/Qsci/qscilexer.h>
#include <QMap>

class Utils
{
public:
    static QsciLexer* TrouverLexer(QString extension);
    static QString getCouleurStyle(QColor couleur);

private:
    static void InitialiserExtensions();
    static QMap<QsciLexer*, QStringList>* m_Extensions;
};

#endif // UTILS_H
