#ifndef DLGCONNEXION_H
#define DLGCONNEXION_H

#include <QDialog>
#include <QSettings>

namespace Ui {
    class dlgConnexion;
}

class dlgConnexion : public QDialog
{
    Q_OBJECT

public:
    explicit dlgConnexion(QWidget *parent = 0);
    ~dlgConnexion();

private:
    Ui::dlgConnexion *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // DLGCONNEXION_H
