#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "add_dialog.h"
#include "QFileInfo"
#include "QFileDialog"
#include "QTextStream"
#include "Vector.h"
#include "QHeaderView"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    ui->tableWidget->setStyleSheet("selection-background-color:#d6b6c6;");
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#fdf8f1;}");
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    setWindowIcon(QIcon(":/images/icons/film.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_triggered()
{
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите создать новый файл?\nНесохраненные изменения будут потеряны.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    ui->tableWidget->setRowCount(0);
    _vector.clear();
    nameOfFile = "";
    setWindowTitle("*" + nameOfFile + " – Фильмы");
}

void MainWindow::on_action_Add_triggered()
{
    Add_Dialog myDialog;
    if (myDialog.exec() == QDialog::Accepted)
    {
        Film t = myDialog.getData();

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(t.getprod()));
        ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0)->setTextColor(QColor(208, 176, 132));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(t.getFilm()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(t.getgenre()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(t.getProfit()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(t.getoutYear()));

        _vector.push_back(t);
        ui->statusBar->showMessage("Запись добавлена.");
        setWindowTitle("*" + nameOfFile + " – Фильмы");
    }
}


void MainWindow::on_action_Exit_triggered()
{
    if (ui->tableWidget->rowCount() > 0 || nameOfFile != "") {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите выйти?\nНесохраненные изменения будут потеряны.");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::No) {
            return;
        }
    }
    exit(0);
}


void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tableWidget->setCurrentCell(-1, -1);
    if (arg1 == "") {
        return;
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    auto find_items = ui->tableWidget->findItems(arg1, Qt::MatchContains);
    int len = find_items.size();
    for (int i = 0; i < len; ++i) {
        auto item = find_items.at(i);
        ui->tableWidget->setItemSelected(item, true);
    }
    ui->tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
    ui->statusBar->showMessage("Найдено " + QString::number(len) + " элементов.");
}


void MainWindow::on_action_Edit_triggered()
{
    auto list = ui->tableWidget->selectedItems();

    if (list.size() > 0) {
        Add_Dialog myDialog;
        myDialog.setprod(list.at(0)->text());
        myDialog.setFilm(list.at(1)->text());
        myDialog.setgenre(list.at(2)->text());
        myDialog.setProfit(list.at(3)->text());
        myDialog.setoutYear(list.at(4)->text());

        QItemSelectionModel *selectModel = ui->tableWidget->selectionModel();
        if (selectModel->hasSelection())
           selectModel->selectedRows().first().row();

        if (myDialog.exec() == QDialog::Accepted)
        {
            Film t = myDialog.getData();
            list.at(0)->setText(t.getprod());
            list.at(1)->setText(t.getFilm());
            list.at(2)->setText(t.getgenre());
            list.at(3)->setText(t.getProfit());
            list.at(4)->setText(t.getoutYear());
            _vector[list.at(0)->row()].setprod(t.getprod());
            _vector[list.at(1)->row()].setFilm(t.getFilm());
            _vector[list.at(2)->row()].setgenre(t.getgenre());
            _vector[list.at(3)->row()].setProfit(t.getProfit());
            _vector[list.at(4)->row()].setoutYear(t.getoutYear());

            ui->statusBar->showMessage("Запись отредактирована.");
            setWindowTitle("*" + nameOfFile + " – Фильмы");
        }
    }
}


void MainWindow::on_tableWidget_cellDoubleClicked(int, int)
{
    MainWindow::on_action_Edit_triggered();
}


void MainWindow::on_action_Delete_triggered()
{
    auto list = ui->tableWidget->selectionModel()->selectedRows();
    if (list.size() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите удалить выделенную строку?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            for (auto k = list.rbegin(); k != list.rend(); ++k) {
                auto index = (*k).row();
                _vector.erase(index);
                ui->tableWidget->removeRow(index);
            }
            ui->statusBar->showMessage("Запись удалена.");
            setWindowTitle("*" + nameOfFile + " – Фильмы");
        }
    } else ui->statusBar->showMessage("Таблица пуста.");
}


void MainWindow::on_action_Clear_triggered()
{
    ui->tableWidget->setColumnWidth(0, 192);
    if (ui->tableWidget->rowCount() > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Внимание");
        msgBox.setText("Вы уверены, что хотите очистить таблицу?");
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        if (msgBox.exec() == QMessageBox::Yes) {
            ui->tableWidget->setRowCount(0);
            _vector.clear();
            ui->statusBar->showMessage("Таблица очищена.");
            setWindowTitle("*" + nameOfFile + " – Фильмы");
        }
    } else ui->statusBar->showMessage("Таблица пуста.");
}


void MainWindow::on_action_Open_triggered(bool isClean)
{
    QString file_name = QFileDialog::getOpenFileName(this, "Открыть файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    QFileInfo check_file(file_name);
    if (check_file.exists() && check_file.isFile()) {
        if (!isClean) {
            on_action_Clear_triggered();
        }
        QFile file(file_name);
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                Film f;
                QString line = in.readLine();
                QStringList strArr = line.split(";");
                if (strArr.size() == 5) { //4
                    f.setprod(strArr[0].simplified());
                    f.setFilm(strArr[1].simplified());
                    f.setgenre(strArr[2].simplified());
                    f.setProfit(strArr[3].simplified());
                    f.setoutYear(strArr[4].simplified());
                    ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, new QTableWidgetItem(f.getprod()));
                    ui->tableWidget->item(ui->tableWidget->rowCount() - 1, 0)->setTextColor(QColor(208, 176, 132));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, new QTableWidgetItem(f.getFilm()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 2, new QTableWidgetItem(f.getgenre()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 3, new QTableWidgetItem(f.getProfit()));
                    ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 4, new QTableWidgetItem(f.getoutYear()));

                    _vector.push_back(f);
                }
            }
            file.close();
            ui->statusBar->showMessage("Записи из файла добавлены.");
            nameOfFile = file_name;
            setWindowTitle(nameOfFile + " – Фильмы");
        } else ui->statusBar->showMessage("Файл '" + file_name + "' не удалось открыть на чтение (" + file.errorString() + ")");
    } else ui->statusBar->showMessage("Файла '" + file_name + "' не существует");
}


void MainWindow::on_action_Save_triggered()
{
    if (nameOfFile == "") {
        MainWindow::on_action_SaveAs_triggered();
        return;
    }
    QFile file(nameOfFile);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream out(&file);
        int len = ui->tableWidget->rowCount();
        for (int i = 0; i < len; ++i) {
            QString prod = ui->tableWidget->item(i, 0)->text();
            QString name = ui->tableWidget->item(i, 1)->text();
            QString genre = ui->tableWidget->item(i, 2)->text();
            QString year = ui->tableWidget->item(i, 3)->text();
            QString outYear = ui->tableWidget->item(i, 4)->text();
            out << prod << ";" << name << ";" << genre << ";" << year << ";" << outYear << "\n";
        }
        file.close();
        ui->statusBar->showMessage("Файл сохранен.");
        setWindowTitle(nameOfFile + " – Фильмы");
    }
}


void MainWindow::on_action_SaveAs_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Сохранить файл...", ".", "CSV files (*.csv);;All files (*.*);;");
    if (file_name != "") {
        nameOfFile = file_name;
        MainWindow::on_action_Save_triggered();
    }
}


void MainWindow::on_action_Merge_triggered()
{
    QString old_file = nameOfFile;
    MainWindow::on_action_Open_triggered(true);
    nameOfFile = old_file;
    ui->statusBar->showMessage("Данные объединены");
    setWindowTitle("*" + nameOfFile + " – Фильмы");
}


void MainWindow::on_action_About_triggered()
{
    QMessageBox::about(this,
                       "О программе",
                       "Курсовая работа по дисциплине ООП\n"
                       "Тема: Класс, характеризующий фильм\n"
                       "Вариант: 7\n"
                       "Выполнила: Зырянова Кристина Андреевна\n"
                       "Группа: ИКПИ-12\n"
                       "Санкт-Петербург\n"
                       "2022 год\n");
}
