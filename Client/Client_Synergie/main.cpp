#include <QtGui/QApplication>
#include "dlgconnexion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dlgConnexion w;
    w.show();

    return a.exec();
}
