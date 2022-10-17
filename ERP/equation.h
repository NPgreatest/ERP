#ifndef EQUATION_H
#define EQUATION_H

#include <QMainWindow>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QMessageBox>
#include<QStandardItemModel>
#include<QString>
namespace Ui {
class equation;
}

class equation : public QMainWindow
{
    Q_OBJECT

public:
    explicit equation(QWidget *parent = nullptr);
    ~equation();
    void Import_Data(bool flag);
private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

private:
    Ui::equation *ui;
    QSqlQuery *query;
    QSqlDatabase db;
    QStandardItemModel* model;
};

#endif // EQUATION_H
