#ifndef ADD_DIALOG_H
#define ADD_DIALOG_H

#include <QDialog>
#include "Film.h"

namespace Ui {
    class Add_Dialog;
}

class Add_Dialog : public QDialog
{
    Q_OBJECT

public:

    explicit Add_Dialog(QWidget *parent = nullptr);
    ~Add_Dialog();
    Film getData();
    void setprod(QString arg);
    void setFilm(QString arg);
    void setgenre(QString arg);
    void setoutYear(QString arg);
    void setProfit(QString arg);

private:
    Ui::Add_Dialog *ui;
};

#endif // ADD_DIALOG_H
