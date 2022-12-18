#include "add_dialog.h"
#include "ui_add_dialog.h"
#include "QPushButton"

Add_Dialog::Add_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Add_Dialog)
{
    ui->setupUi(this);
    setFixedSize(size());

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("OK");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Отмена");
    setWindowIcon(QIcon(":/images/icons/film.png"));
}

Add_Dialog::~Add_Dialog()
{
    delete ui;
}

void Add_Dialog::setprod(QString arg) {
    ui->lineEdit->setText(arg);
}

void Add_Dialog::setFilm(QString arg) {
    ui->lineEdit_2->setText(arg);
}

void Add_Dialog::setgenre(QString arg) {
    ui->lineEdit_3->setText(arg);
}

void Add_Dialog::setoutYear(QString arg) {
    ui->lineEdit_4->setText(arg);
}

void Add_Dialog::setProfit(QString arg) {
    ui->lineEdit_5->setText(arg);
}

Film Add_Dialog::getData() {
    Film result;
    result.setprod(ui->lineEdit->text().simplified().replace(";", ","));
    result.setFilm(ui->lineEdit_2->text().simplified().replace(";", ","));
    result.setgenre(ui->lineEdit_3->text().simplified().replace(";", ","));
    result.setoutYear(ui->lineEdit_4->text().simplified().replace(";", ","));
    result.setProfit(ui->lineEdit_5->text().simplified().replace(";", ","));
    return result;
}
